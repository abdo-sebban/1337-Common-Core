/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:05:32 by selbouka          #+#    #+#             */
/*   Updated: 2024/11/15 19:53:33 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*pd;
	char		*ps;

	pd = (char *)dest;
	ps = (char *)src;
	if (ps < pd)
	{
		while (n-- > 0)
			pd[n] = ps[n];
		return (dest);
	}
	return (ft_memcpy (dest, src, n));
}
