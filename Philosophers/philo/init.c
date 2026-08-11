/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:21:17 by asebban           #+#    #+#             */
/*   Updated: 2025/06/15 10:56:36 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	destroy_forks_mutexes(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

static	int	init_forks_mutexes(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->numbers_of_philos);
	if (!info->forks)
		return (err("Error: Mutex malloc failed\n"));
	i = 0;
	while (i < info->numbers_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
		{
			destroy_forks_mutexes(info->forks, i);
			return (err("Error: Mutex init failed\n"));
		}
		i++;
	}
	return (0);
}

static	int	init_other_mutexes(t_info *info)
{
	if (pthread_mutex_init(&info->write_lock, NULL))
		return (err("Error: Write mutex init failed\n"));
	if (pthread_mutex_init(&info->meal_lock, NULL))
	{
		pthread_mutex_destroy(&info->write_lock);
		return (err("Error: Meal mutex init failed\n"));
	}
	if (pthread_mutex_init(&info->death_lock, NULL))
	{
		pthread_mutex_destroy(&info->meal_lock);
		pthread_mutex_destroy(&info->write_lock);
		return (err("Error: Death mutex init failed\n"));
	}
	return (0);
}

int	init_mutexes(t_info *info)
{
	if (init_forks_mutexes(info))
		return (1);
	if (init_other_mutexes(info))
	{
		destroy_forks_mutexes(info->forks, info->numbers_of_philos);
		return (1);
	}
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(t_philo) * info->numbers_of_philos);
	if (!info->philos)
		return (err("Error: Philos malloc failed\n"));
	i = 0;
	while (i < info->numbers_of_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].meals_eaten = 0;
		info->philos[i].last_meal_time = info->time_start;
		info->philos[i].is_eating = 0;
		info->philos[i].left_fork = i;
		info->philos[i].right_fork = (i + 1) % info->numbers_of_philos;
		info->philos[i].info = info;
		i++;
	}
	return (0);
}
