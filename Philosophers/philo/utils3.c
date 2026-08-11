/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:10:15 by asebban           #+#    #+#             */
/*   Updated: 2025/06/15 10:08:05 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->death_lock);
	if (info->someone_died)
	{
		pthread_mutex_unlock(&info->death_lock);
		return ;
	}
	pthread_mutex_unlock(&info->death_lock);
	pthread_mutex_lock(&info->meal_lock);
	philo->is_eating = 1;
	philo->last_meal_time = get_time_start();
	philo->meals_eaten++;
	pthread_mutex_unlock(&info->meal_lock);
	if (check_death1(philo))
		return ;
	print_status(philo, "is eating");
	if (check_death1(philo))
		return ;
	smart_sleep(info->time_to_eat, philo);
	pthread_mutex_lock(&info->meal_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&info->meal_lock);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	if (check_death1(philo))
		return ;
	print_status(philo, "is sleeping");
	if (check_death1(philo))
		return ;
	smart_sleep(philo->info->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	if (check_death1(philo))
		return ;
	print_status(philo, "is thinking");
	if (check_death1(philo))
		return ;
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	smart_sleep(philo->info->time_to_die, philo);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
}
