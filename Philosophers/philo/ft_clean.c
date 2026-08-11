/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:59:51 by asebban           #+#    #+#             */
/*   Updated: 2025/06/15 10:23:56 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->numbers_of_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->death_lock);
	free(info->forks);
	free(info->philos);
	free(info);
}
