/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:21:33 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/15 12:29:24 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strndup1(const char *s, size_t n)
{
	char	*p;

	p = ft_malloc((n + 1), 1);
	if (!p)
		return (NULL);
	ft_memcpy(p, s, n);
	p[n] = '\0';
	return (p);
}

int	is_heredoc(const char *s)
{
	if (s[0] == '<' && s[1] == '<')
		return (2);
	return (0);
}
