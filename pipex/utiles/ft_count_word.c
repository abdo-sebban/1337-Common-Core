/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:00:33 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 11:35:56 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/pipex_bonus.h"

static	int	ft_check_unclosed_quotes(const char *str)
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
		i++;
	}
	return (in_quote);
}

int	ft_handle_quotes(char *str, int *i, int *in_quote, char *quote_type)
{
	if ((str[*i] == '\'' || str[*i] == '"'))
	{
		if (!(*in_quote))
		{
			*in_quote = 1;
			*quote_type = str[*i];
		}
		else if (str[*i] == *quote_type)
			*in_quote = 0;
	}
	return (*in_quote);
}

int	ft_count_word(char *str, char c)
{
	int		i;
	int		counter;
	int		new_word;
	int		in_quote;
	char	quote_type;

	i = 0;
	counter = 0;
	new_word = 1;
	in_quote = 0;
	quote_type = 0;
	if (ft_check_unclosed_quotes(str))
		return (-1);
	while (str[i])
	{
		in_quote = ft_handle_quotes(str, &i, &in_quote, &quote_type);
		if (new_word && (str[i] != c || in_quote))
		{
			counter++;
			new_word = 0;
		}
		if (str[i++] == c && !in_quote)
			new_word = 1;
	}
	return (counter);
}
