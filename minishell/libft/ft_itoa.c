/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:53:02 by selbouka          #+#    #+#             */
/*   Updated: 2025/04/21 12:21:36 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	long	nbr;
	char	*str;
	int		ln;

	ln = len(nb);
	nbr = nb;
	if (nbr == 0)
		return (ft_strdup("0"));
	str = ft_malloc (ln + 1, 1);
	if (!str)
		return (NULL);
	str[ln--] = '\0';
	if (nb < 0)
	{
		nbr *= -1;
		str[0] = '-';
	}
	while (nbr > 0)
	{
		str[ln] = nbr % 10 + 48;
		nbr = nbr / 10;
		ln--;
	}
	return (str);
}
