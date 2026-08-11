/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:48:09 by selbouka          #+#    #+#             */
/*   Updated: 2025/04/21 12:22:24 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*ptr;
	int		j;
	int		inc;

	if (!s1 || !set)
		return (NULL);
	inc = 0;
	i = 0;
	while (check(s1[i], set) == 1)
		i++;
	j = ft_strlen(s1);
	while (check(s1[j - 1], set) == 1)
		j--;
	if ((j - i + 1) < 0)
		return (ft_strdup(""));
	ptr = ft_malloc((j - i + 1) * sizeof(char), 1);
	if (!ptr)
		return (NULL);
	while (i < j)
		ptr[inc++] = s1[i++];
	return (ptr[inc] = '\0', ptr);
}
