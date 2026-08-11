/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:45:35 by asebban           #+#    #+#             */
/*   Updated: 2025/05/30 16:38:34 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	write(2, s, ft_strlen(s));
}

void	ft_usage(void)
{
	ft_putstr(YELLOW);
	ft_putstr("USAGE: \n");
	ft_putstr(RESET);
	ft_putstr(BLUE);
	ft_putstr("./philo number_of_philosophers time_to_die\n");
	ft_putstr("     time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n");
	ft_putstr(RESET);
}

int	err(char *str)
{
	ft_putstr(RED);
	ft_putstr(str);
	ft_putstr(RESET);
	return (1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
