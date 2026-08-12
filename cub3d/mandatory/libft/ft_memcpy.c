/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:49:21 by asebban           #+#    #+#             */
/*   Updated: 2024/11/08 09:33:42 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t num_bytes)
{
	unsigned char		*dest;
	const unsigned char	*src;
	size_t				i;

	dest = (unsigned char *)to;
	src = (const unsigned char *)from;
	if (!to && !from)
		return (0);
	if (num_bytes == 0 || to == from)
		return (to);
	i = 0;
	while (i < num_bytes)
	{
		dest[i] = src[i];
		i++;
	}
	return (to);
}
