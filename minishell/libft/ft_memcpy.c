/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:10:31 by selbouka          #+#    #+#             */
/*   Updated: 2024/11/15 16:32:30 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*pd;
	char	*ps;
	size_t	i;

	i = 0;
	pd = (char *)dest;
	ps = (char *)src;
	if (pd == ps)
		return (dest);
	while (i < n)
	{
		pd[i] = ps[i];
		i++;
	}
	return (dest);
}
