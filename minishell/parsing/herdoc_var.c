/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:35:55 by asebban           #+#    #+#             */
/*   Updated: 2025/05/11 17:08:29 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	size_t	calc_replace_size(const char *input, t_shell *shell)
{
	size_t	i;
	size_t	total;
	size_t	var_len;

	i = 0;
	total = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			var_len = 0;
			calc_var_length(input, &i, shell, &var_len);
			total += var_len;
		}
		else
		{
			total++;
			i++;
		}
	}
	return (total);
}

size_t	extract_var_name(const char *input,
		t_replinfo *info, char *name_buf)
{
	size_t	idx;
	size_t	start;
	size_t	vlen;

	idx = info->i;
	start = idx + 1;
	vlen = 0;
	while (ft_isalnum(input[start + vlen]) || input[start + vlen] == '_')
		vlen++;
	ft_strncpy(name_buf, input + start, vlen);
	name_buf[vlen] = '\0';
	info->i = start + vlen;
	return (vlen);
}

static size_t	handle_dollar_case(const char *input, char *out,
		t_replinfo *info, t_shell *shell)
{
	size_t	idx;

	idx = info->i;
	if (input[idx + 1] == '?')
	{
		info->o = append_exit_status(out, info->o);
		info->i = idx + 2;
	}
	else if (ft_isalpha(input[idx + 1]) || input[idx + 1] == '_')
		return (handle_alpha_case(input, out, info, shell));
	else
	{
		out[info->o++] = '$';
		info->i = idx + 1;
	}
	return (info->i);
}

static	size_t	fill_replaced_vars(char *out, const char *input, t_shell *shell)
{
	t_replinfo	info;
	size_t		len;

	len = ft_strlen(input);
	info.i = 0;
	info.o = 0;
	while (info.i < len)
	{
		if (input[info.i] == '$')
			handle_dollar_case(input, out, &info, shell);
		else
			out[info.o++] = input[info.i++];
	}
	out[info.o] = '\0';
	return (info.o);
}

char	*replace_vars_heredoc(char *input, t_shell *shell)
{
	size_t	needed;
	char	*out;

	if (!input)
		return (NULL);
	needed = calc_replace_size(input, shell);
	out = ft_malloc(needed + 1, 1);
	if (!out)
		return (NULL);
	fill_replaced_vars(out, input, shell);
	return (out);
}
