/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:17:27 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 11:36:12 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/pipex_bonus.h"

int	ft_str_len_sep(char *str, char set)
{
	int		i;
	int		in_quote;
	char	quote_type;

	i = 0;
	in_quote = 0;
	quote_type = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!in_quote)
			{
				in_quote = 1;
				quote_type = str[i];
			}
			else if (str[i] == quote_type)
				in_quote = 0;
		}
		else if (str[i] == set && !in_quote)
			break ;
		i++;
	}
	return (i);
}

static	char	**split_helper(const char *str, char **strings,
			char charset, int i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == charset)
			j++;
		if (str[j])
		{
			strings[i] = ft_allocation((char *)(str + j), charset);
			if (strings[i] == NULL)
			{
				while (--i >= 0)
					free(strings[i]);
				free(strings);
				return (NULL);
			}
			i++;
		}
		j += ft_str_len_sep((char *)(str + j), charset);
	}
	strings[i] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_count;
	char	**strings;

	i = 0;
	if (!s)
		return (NULL);
	word_count = ft_count_word((char *)s, c);
	if (word_count == -1)
	{
		write(2, "\033[31mInvalid argument\n\e[0m", 27);
		return (NULL);
	}
	strings = (char **)malloc((word_count + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	strings = split_helper(s, strings, c, i);
	return (strings);
}
