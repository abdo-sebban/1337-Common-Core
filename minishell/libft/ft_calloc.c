/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:42:05 by selbouka          #+#    #+#             */
/*   Updated: 2025/04/21 14:06:38 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	if (size && n && (n * size) / size != n)
		return (NULL);
	p = ft_malloc(n * size, 1);
	if (!p)
		return (NULL);
	ft_bzero(p, n * size);
	return (p);
}
