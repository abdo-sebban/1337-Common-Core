/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:07:36 by asebban           #+#    #+#             */
/*   Updated: 2024/11/25 10:05:34 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		count += ft_putchar('-');
		if (count < 0)
			return (-1);
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr(n / 10);
		if (count < 0)
			return (-1);
	}
	count += ft_putchar((n % 10) + '0');
	if (count < 0)
		return (-1);
	return (count);
}
