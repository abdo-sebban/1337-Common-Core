/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:14:37 by asebban           #+#    #+#             */
/*   Updated: 2025/05/24 20:38:42 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*append_segment(char *res, const char *seg, int len)
{
	char	*new_res;
	int		old_len;

	old_len = ft_strlen(res);
	new_res = ft_malloc(old_len + len + 1, 1);
	if (!new_res)
		return (NULL);
	ft_strcpy(new_res, res);
	ft_strncat(new_res, seg, len);
	return (new_res);
}

int	parse_quoted(const char *s, int *i, char **res)
{
	char	quote;
	int		start;
	int		len;

	quote = s[(*i)++];
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	len = *i - start;
	*res = append_segment(*res, &s[start], len);
	if (!*res)
		return (0);
	if (s[*i] == quote)
		(*i)++;
	return (1);
}

int	parse_literal(const char *s, int *i, char **res)
{
	int	start;
	int	len;

	start = *i;
	while (s[*i] && s[*i] != ' '
		&& ft_operator_len(&s[*i]) == 0
		&& s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	len = *i - start;
	*res = append_segment(*res, &s[start], len);
	if (!*res)
		return (0);
	return (1);
}

char	*parse_token(const char *s, int *i)
{
	char	*res;

	res = ft_malloc(1, 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (s[*i] && s[*i] != ' ' && ft_operator_len(&s[*i]) == 0)
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			if (!parse_quoted(s, i, &res))
				return (NULL);
		}
		else
		{
			if (!parse_literal(s, i, &res))
				return (NULL);
		}
	}
	return (res);
}

char	*get_next_token(const char *s, int *index, int *is_op)
{
	int		i;
	int		op_len;
	char	*tok;

	*is_op = 0;
	i = skip_spaces(s, *index);
	if (!s[i])
		return (NULL);
	if (s[i] == '\'' || s[i] == '"')
		tok = parse_token(s, &i);
	else
	{
		op_len = ft_operator_len(&s[i]);
		if (op_len > 0)
		{
			tok = ft_dup_token(&s[i], op_len);
			*is_op = 1;
			i += op_len;
		}
		else
			tok = parse_token(s, &i);
	}
	*index = i;
	return (tok);
}
