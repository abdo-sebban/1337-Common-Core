/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:47:52 by asebban           #+#    #+#             */
/*   Updated: 2025/05/11 10:57:28 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	even_handler(const char *input, int count,
			char *out, int *out_pos)
{
	char	quote;
	int		i;
	int		j;

	quote = input[count];
	i = count + 1;
	if (count % 2 != 0)
		count -= 1;
	j = 0;
	while (j < count)
	{
		out[(*out_pos)++] = '$';
		j++;
	}
	out[(*out_pos)++] = quote;
	while (input[i] && input[i] != quote)
		out[(*out_pos)++] = input[i++];
	if (input[i] == quote)
		out[(*out_pos)++] = input[i];
	if (input[i])
		return (i + 1);
	else
		return (i);
}

static int	handle_quotes(char *input, char *out, int *i, int *out_pos)
{
	char	quote;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote = input[*i];
		out[(*out_pos)++] = input[(*i)++];
		while (input[*i] && input[*i] != quote)
			out[(*out_pos)++] = input[(*i)++];
		if (input[*i] == quote)
			out[(*out_pos)++] = input[(*i)++];
		return (1);
	}
	return (0);
}

static int	handle_dollars(char *input, char *out, int *i, int *out_pos)
{
	int	count;
	int	consumed;

	if (input[*i] == '$')
	{
		count = 0;
		while (input[*i + count] && input[*i + count] == '$')
			count++;
		if (input[*i + count]
			&& (input[*i + count] == '\'' || input[*i + count] == '\"'))
		{
			consumed = even_handler(input + *i, count, out, out_pos);
			*i += consumed;
			return (1);
		}
	}
	return (0);
}

static int	process_quotes_and_dollars(char *input, char *out,
			int *i, int *out_pos)
{
	if (handle_quotes(input, out, i, out_pos))
		return (1);
	if (handle_dollars(input, out, i, out_pos))
		return (1);
	return (0);
}

char	*handle_dollar_quotes(char *input)
{
	char	*out;
	int		out_pos;
	int		i;

	if (!input)
		return (NULL);
	out = ft_malloc(ft_strlen(input) + 1, 1);
	out_pos = 0;
	i = 0;
	while (input[i])
	{
		if (process_quotes_and_dollars(input, out, &i, &out_pos))
			continue ;
		out[out_pos++] = input[i++];
	}
	out[out_pos] = '\0';
	return (out);
}
