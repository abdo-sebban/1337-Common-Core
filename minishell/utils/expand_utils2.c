/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:30:37 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 10:52:54 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_chunk(char **dst, size_t *dst_len, const char *src, size_t len)
{
	char	*new_dst;

	new_dst = ft_realloc(*dst, *dst_len, *dst_len + len + 1);
	if (!new_dst)
		return ;
	*dst = new_dst;
	ft_memcpy(*dst + *dst_len, src, len);
	*dst_len += len;
	(*dst)[*dst_len] = '\0';
}

size_t	process_double_redirect(char **out, size_t *out_len, int flag)
{
	if (flag == 1)
		append_chunk(out, out_len, "'>>'", 4);
	else
		append_chunk(out, out_len, "'<<'", 4);
	return (2);
}

size_t	process_single_operator(char **out,
		size_t *out_len, char sym)
{
	char	quoted[4];

	quoted[0] = '\'';
	quoted[1] = sym;
	quoted[2] = '\'';
	quoted[3] = '\0';
	append_chunk(out, out_len, quoted, 3);
	return (1);
}

size_t	process_regular_char(char **out,
		size_t *out_len, const char *in)
{
	append_chunk(out, out_len, in, 1);
	return (1);
}

void	app_result(char **pres)
{
	char	**tokens;
	char	*result;
	char	*tmp;
	size_t	i;

	if (!pres || !*pres)
		return ;
	tokens = ft_split1(*pres, ' ');
	result = ft_strdup("");
	i = 0;
	while (tokens[i])
	{
		tmp = ft_strjoin("\"", tokens[i]);
		tokens[i] = ft_strjoin(tmp, "\"");
		if (i > 0)
		{
			tmp = ft_strjoin(" ", tokens[i]);
			tokens[i] = tmp;
		}
		tmp = ft_strjoin(result, tokens[i]);
		result = tmp;
		i++;
	}
	*pres = result;
}
