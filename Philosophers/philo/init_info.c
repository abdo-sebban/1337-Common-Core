/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:14:27 by asebban           #+#    #+#             */
/*   Updated: 2025/06/01 12:11:55 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	set_default_values(t_info *info)
{
	info->numbers_of_philos = 0;
	info->time_to_die = 0;
	info->time_to_eat = 0;
	info->time_to_sleep = 0;
	info->must_eat_count = 0;
	info->someone_died = 0;
	info->all_ate = 0;
	info->time_start = 0;
	info->forks = NULL;
	info->philos = NULL;
}

t_info	*alloc_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	set_default_values(info);
	return (info);
}
