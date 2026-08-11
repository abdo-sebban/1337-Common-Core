/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:50:48 by asebban           #+#    #+#             */
/*   Updated: 2024/11/28 09:42:58 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(const char *str)
{
	int	count;
	int	result;

	count = 0;
	if (!str)
	{
		return (ft_putstr("(null)"));
	}
	while (str[count])
	{
		result = write(1, &str[count], 1);
		if (result < 0)
		{
			return (-1);
		}
		count++;
	}
	return (count);
}
