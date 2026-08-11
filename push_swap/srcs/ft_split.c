/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:09:03 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 12:41:11 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_count_word(char *str, char c)
{
	int	i;
	int	counter;
	int	new_word;

	i = 0;
	counter = 0;
	new_word = 1;
	while (str[i])
	{
		if (new_word == 1 && str[i] != c)
		{
			counter++;
			new_word = 0;
		}
		if (str[i] == c)
			new_word = 1;
		i++;
	}
	return (counter);
}

static int	ft_str_len_sep(char *str, char set)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != set)
		i++;
	return (i);
}

static char	*ft_allocation(char *str, char set)
{
	int		len;
	int		i;
	char	*word;

	i = 0;
	len = ft_str_len_sep(str, set);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**split_helper(const char *str, char **strings, char charset, int i)
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
		while (str[j] && str[j] != charset)
			j++;
	}
	strings[i] = NULL;
	return (strings);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		word_countre;
	char	**strings;

	if (!s)
		return (NULL);
	i = 0;
	word_countre = ft_count_word((char *)s, c);
	strings = (char **)malloc((word_countre + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	strings = split_helper(s, strings, c, i);
	return (strings);
}
