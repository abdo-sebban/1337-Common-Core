/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_low_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:58:14 by asebban           #+#    #+#             */
/*   Updated: 2024/11/25 10:00:17 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_low_hex(unsigned int num)
{
	char	*hexa;
	char	buffer[16];
	int		count;
	int		i;

	hexa = "0123456789abcdef";
	i = 0;
	count = 0;
	if (num == 0)
	{
		return (write(1, "0", 1));
	}
	while (num)
	{
		buffer[i] = hexa[num % 16];
		num /= 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		count += write(1, &buffer[i], 1);
	}
	return (count);
}
