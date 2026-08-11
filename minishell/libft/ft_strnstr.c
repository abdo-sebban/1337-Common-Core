/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:16:46 by selbouka          #+#    #+#             */
/*   Updated: 2024/11/15 11:25:50 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(const char *big, const char *lit, size_t n)
{
	size_t	i;

	i = 0;
	while (lit[i])
	{
		if (lit[i] == big[i] && i < n)
			i++;
		else
			return (0);
	}
	return (1);
}

char	*ft_strnstr(const char *haystack,	const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < n && haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			if (check(&haystack[i], needle, n - i) == 1)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
