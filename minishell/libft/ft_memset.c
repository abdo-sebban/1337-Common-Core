/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:15:27 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/06 18:06:08 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	if (!str)
		return (NULL);
	ptr = (unsigned char *)str;
	i = 0;
	while (i < n)
		ptr[i++] = (unsigned char)c;
	return (str);
}
