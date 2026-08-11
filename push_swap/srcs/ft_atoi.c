/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:27:03 by asebban           #+#    #+#             */
/*   Updated: 2025/02/23 14:28:33 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	skips(const char *str, int *sign)
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

long	ft_atoi(const char *str)
{
	long	nbr;
	int		i;
	int		sign;
	long	tmp;

	nbr = 0;
	sign = 1;
	tmp = 0;
	i = skips(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = nbr;
		nbr = nbr * 10 + str[i] - '0';
		if (nbr / 10 != tmp && sign == 1)
			return (2147483648);
		else if (nbr / 10 != tmp && sign == -1)
			return (2147483648);
		i++;
	}
	return (nbr * sign);
}
