/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:15:09 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/15 21:06:59 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	counter2(const char *s, char sep, int *i, char *quote)
{
	while (s[*i])
	{
		if ((s[*i] == '\'' || s[*i] == '\"'))
		{
			if (!(*quote))
				*quote = s[*i];
			else if ((*quote) == s[*i])
				*quote = 0;
		}
		if (s[*i] == sep && !(*quote))
			break ;
		(*i)++;
	}
}

static int	counter(const char *s, char sep)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == sep && !quote)
			i++;
		if (s[i])
			count++;
		counter2(s, sep, &i, &quote);
	}
	return (count);
}

int	loop2(const char *s, char sep, int *j, char *quote)
{
	int	start;

	if (s[*j] == '\'' || s[*j] == '\"')
	{
		*quote = s[*j];
	}
	while (s[*j] == sep && !(*quote))
		(*j)++;
	start = *j;
	while (s[*j])
	{
		if ((s[*j] == '\'' || s[*j] == '\"'))
		{
			if (!(*quote))
				*quote = s[*j];
			else if ((*quote) == s[*j])
				*quote = 0;
		}
		if (s[*j] == sep && !(*quote))
			break ;
		(*j)++;
	}
	return (start);
}

static char	**loop(const char *s, char **array, char sep)
{
	int		i;
	int		j;
	int		start;
	char	quote;
	char	*tmp;

	i = 0;
	j = 0;
	quote = 0;
	while (s[j])
	{
		start = loop2(s, sep, &j, &quote);
		if (j > start)
		{
			tmp = ft_strndup(s + start, s[j]);
			if (!tmp)
				return (NULL);
			array[i++] = tmp;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split1(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)ft_malloc(sizeof(char *) * (counter(s, c) + 1), 1);
	if (!array)
		return (NULL);
	return (loop(s, array, c));
}
