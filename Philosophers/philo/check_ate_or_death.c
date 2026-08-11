/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ate_or_death.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:30:11 by asebban           #+#    #+#             */
/*   Updated: 2025/06/01 12:07:00 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_info *info)
{
	long long	current_time;
	long long	time_since_last_meal;
	int			is_eating;

	pthread_mutex_lock(&info->meal_lock);
	current_time = get_time_start();
	is_eating = philo->is_eating;
	time_since_last_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&info->meal_lock);
	if (!is_eating && time_since_last_meal >= info->time_to_die)
	{
		if (!check_death1(philo))
		{
			pthread_mutex_lock(&info->death_lock);
			info->someone_died = 1;
			pthread_mutex_unlock(&info->death_lock);
			pthread_mutex_lock(&info->write_lock);
			printf("%lld %zu died\n", \
current_time - info->time_start, philo->id);
			pthread_mutex_unlock(&info->write_lock);
		}
		return (1);
	}
	return (0);
}

int	check_all_ate(t_info *info)
{
	int	i;
	int	all_ate;

	if (info->must_eat_count == -1)
		return (0);
	i = 0;
	all_ate = 1;
	while (i < info->numbers_of_philos)
	{
		pthread_mutex_lock(&info->meal_lock);
		if (info->philos[i].meals_eaten < info->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&info->meal_lock);
		if (!all_ate)
			break ;
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&info->death_lock);
		info->someone_died = 1;
		pthread_mutex_unlock(&info->death_lock);
		return (1);
	}
	return (0);
}
