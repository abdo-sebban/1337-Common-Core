/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:07:20 by asebban           #+#    #+#             */
/*   Updated: 2025/07/23 21:07:18 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	len_number(int number)
{
	unsigned int	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length += 1;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

static void	fill_string1(char *string, unsigned int number, unsigned int length)
{
	while (number != 0)
	{
		string[length - 1] = (number % 10) + '0';
		number /= 10;
		length--;
	}
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	number;
	unsigned int	length;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = len_number(n);
	string = (char *)malloc(sizeof(char) * (length + 1));
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		number = -n;
	}
	else
		number = n;
	string[length] = '\0';
	if (number == 0)
		string[0] = '0';
	else
		fill_string1(string, number, length);
	return (string);
}
