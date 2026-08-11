/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uns_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:57:31 by asebban           #+#    #+#             */
/*   Updated: 2024/11/25 10:03:26 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_uns_nbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_put_uns_nbr(n / 10);
	if (count < 0)
		return (-1);
	count += ft_putchar((n % 10) + '0');
	return (count);
}
