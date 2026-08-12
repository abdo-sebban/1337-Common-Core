/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:00:17 by asebban           #+#    #+#             */
/*   Updated: 2024/11/11 11:12:01 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_ned;

	if (!*needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	len_ned = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i + len_ned <= len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (j == len_ned)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
