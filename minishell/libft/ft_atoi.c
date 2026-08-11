/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:12:22 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/16 11:32:04 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_atoi(const char *str)
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
			return (-1);
		else if (nbr / 10 != tmp && sign == -1)
			return (0);
		i++;
	}
	return ((int)nbr * sign);
}
