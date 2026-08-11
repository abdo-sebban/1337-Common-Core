/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:14:35 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 17:28:11 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_spaces(const char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

char	*ft_dup_token(const char *str, int len)
{
	char	*s;
	int		i;

	if (!str || len <= 0)
		return (NULL);
	s = (char *)ft_malloc(len + 1, 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_operator_len(const char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	else if (s[0] == '>' || s[0] == '<' || s[0] == '|')
		return (1);
	return (0);
}

int	advance_token(const char *s, int idx)
{
	int		op_len;
	char	quote;

	op_len = ft_operator_len(&s[idx]);
	if (op_len > 0)
		return (idx + op_len);
	while (s[idx] && s[idx] != ' ' && ft_operator_len(&s[idx]) == 0)
	{
		if (s[idx] == '\'' || s[idx] == '"')
		{
			quote = s[idx++];
			while (s[idx] && s[idx] != quote)
				idx++;
			if (s[idx] == quote)
				idx++;
		}
		else
			idx++;
	}
	return (idx);
}

int	count_tokens(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		count++;
		i = advance_token(s, i);
	}
	return (count);
}
