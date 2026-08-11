/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:31:36 by asebban           #+#    #+#             */
/*   Updated: 2024/11/08 08:32:22 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t counter, size_t size)
{
	void	*ptr;
	size_t	size_alloc;

	if (counter != 0 && size > ((size_t) - 1) / counter)
		return (NULL);
	if (counter == 0 || size == 0)
		return (malloc(0));
	else
		size_alloc = counter * size;
	ptr = malloc(size_alloc);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, size_alloc);
	return (ptr);
}
