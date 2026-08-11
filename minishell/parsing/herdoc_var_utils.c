/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:20:33 by asebban           #+#    #+#             */
/*   Updated: 2025/05/11 16:36:17 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	buf_append(char *out, size_t o, const char *str)
{
	size_t	k;

	k = 0;
	while (str && str[k])
		out[o++] = str[k++];
	return (o);
}

size_t	append_exit_status(char *out, size_t o)
{
	char	buf[12];
	int		status;

	status = exit_status(EXIT_GET, 0);
	int_to_str(status, buf);
	return (buf_append(out, o, buf));
}

void	append_env_var(char *out, const char *start,
		t_shell *shell, size_t info[2])
{
	char	name[256];
	char	*val;

	ft_strncpy(name, start, info[1]);
	name[info[1]] = '\0';
	val = get_env_value(shell->env, name);
	if (val)
		info[0] = buf_append(out, info[0], val);
}

void	handle_variable_name(const char *input,
		size_t *idx, t_shell *shell, size_t *out_len)
{
	size_t	start;
	size_t	vlen;
	char	name[256];
	char	*val;

	start = *idx + 1;
	vlen = 0;
	while (ft_isalnum(input[start + vlen]) || input[start + vlen] == '_')
		vlen++;
	ft_strncpy(name, input + start, vlen);
	name[vlen] = '\0';
	val = get_env_value(shell->env, name);
	if (val)
		*out_len = ft_strlen(val);
	else
		*out_len = 0;
	*idx = start + vlen;
}

void	calc_var_length(const char *input,
		size_t *idx, t_shell *shell, size_t *out_len)
{
	char	buf[12];
	int		status;

	if (input[*idx + 1] == '?')
	{
		status = exit_status(EXIT_GET, 0);
		int_to_str(status, buf);
		*out_len = ft_strlen(buf);
		*idx += 2;
	}
	else if (ft_isalpha(input[*idx + 1]) || input[*idx + 1] == '_')
		handle_variable_name(input, idx, shell, out_len);
	else
	{
		*out_len = 1;
		(*idx)++;
	}
}
