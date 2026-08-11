/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:03:29 by asebban           #+#    #+#             */
/*   Updated: 2024/11/25 09:59:42 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned long num)
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
		return (write(1, "0x0", 3));
	}
	count += write(1, "0x", 2);
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
