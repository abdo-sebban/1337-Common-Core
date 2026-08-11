/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:04:00 by asebban           #+#    #+#             */
/*   Updated: 2025/06/15 10:40:53 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	long	get_time_start(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static	int	ft_skip_char(const char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long	number;
	int		i;
	int		sign;
	int		digit;

	number = 0;
	sign = 1;
	i = ft_skip_char(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (sign == 1 && (number > (INT_MAX - digit) / 10))
			return (-1);
		if (sign == -1 && (-number < (INT_MIN + digit) / 10))
			return (0);
		number = number * 10 + digit;
		i++;
	}
	return ((int)(number * sign));
}

void	print_status(t_philo *philo, char *str)
{
	long long	time;
	int			died;

	if (check_death1(philo))
		return ;
	pthread_mutex_lock(&philo->info->death_lock);
	died = philo->info->someone_died;
	pthread_mutex_unlock(&philo->info->death_lock);
	if (died == 1)
		return ;
	pthread_mutex_lock(&philo->info->write_lock);
	time = get_time_start() - philo->info->time_start;
	pthread_mutex_lock(&philo->info->death_lock);
	died = philo->info->someone_died;
	pthread_mutex_unlock(&philo->info->death_lock);
	if (died == 1)
	{
		pthread_mutex_unlock(&philo->info->write_lock);
		return ;
	}
	printf("%lld %zu %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->write_lock);
}

void	smart_sleep(long long time, t_philo *philo)
{
	long long	start;

	start = get_time_start();
	while (!check_death1(philo))
	{
		if (get_time_start() - start >= time)
			break ;
		usleep(500);
	}
}
