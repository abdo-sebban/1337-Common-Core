/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:15:17 by asebban           #+#    #+#             */
/*   Updated: 2025/06/01 12:20:46 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (1)
	{
		pthread_mutex_lock(&info->death_lock);
		if (info->someone_died)
		{
			pthread_mutex_unlock(&info->death_lock);
			break ;
		}
		pthread_mutex_unlock(&info->death_lock);
		i = 0;
		while (i < info->numbers_of_philos)
		{
			if (check_death(&info->philos[i], info))
				return (NULL);
			i++;
		}
		if (check_all_ate(info))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
