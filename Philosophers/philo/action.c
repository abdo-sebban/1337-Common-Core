/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:46:39 by asebban           #+#    #+#             */
/*   Updated: 2025/06/01 12:01:40 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_eaten_enough(t_philo *philo)
{
	t_info	*info;
	int		enough;

	enough = 0;
	info = philo->info;
	if (info->must_eat_count > 0)
	{
		pthread_mutex_lock(&info->meal_lock);
		enough = (philo->meals_eaten >= info->must_eat_count);
		pthread_mutex_unlock(&info->meal_lock);
	}
	return (enough);
}

bool	check_death1(t_philo *philo)
{
	bool	died;

	pthread_mutex_lock(&philo->info->death_lock);
	died = philo->info->someone_died;
	pthread_mutex_unlock(&philo->info->death_lock);
	return (died);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->info->numbers_of_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		smart_sleep(philo->info->time_to_eat / 2, philo);
	while (1)
	{
		if (check_death1(philo))
			break ;
		take_forks(philo);
		if (check_death1(philo))
		{
			drop_forks(philo);
			break ;
		}
		(eat(philo), drop_forks(philo));
		if (has_eaten_enough(philo))
			break ;
		if (check_death1(philo))
			break ;
		think(philo);
	}
	return (NULL);
}
