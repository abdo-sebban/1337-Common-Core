/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:55:45 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/14 18:41:12 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(const char *s, char n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == n)
			i++;
		if (s[i])
			count++;
		while (s[i] != n && s[i])
			i++;
	}
	return (count);
}

char	*ft_strndup(const char *str, char n)
{
	int		len;
	int		i;
	char	*s;

	len = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[len] != n && str[len])
		len++;
	s = ft_malloc (len + 1, 1);
	if (s == NULL)
		return (NULL);
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	**loop(const char *s, char **array, int c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		if (s[j] != '\0')
		{
			tmp = ft_strndup(s + j, c);
			if (!tmp)
				return (NULL);
			else
				array[i++] = tmp;
		}
		while (s[j] != c && s[j])
			j++;
	}
	return (array[i] = NULL, array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)ft_malloc(sizeof(char *) * (counter(s, c) + 1), 1);
	if (!array)
		return (NULL);
	return (loop(s, array, c));
}
