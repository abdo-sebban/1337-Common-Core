/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:47:45 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 18:01:44 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_var(const char *seg, t_shell *shell,
		char *result, int ptrs[3])
{
	int		start;
	int		len;
	char	*name;
	char	*val;

	1 && (start = ptrs[0] + 1, len = var_name_len1(seg, start));
	name = ft_malloc(len + 1, 1);
	if (!name)
		return ;
	ft_strncpy(name, &seg[start], len);
	1 && (name[len] = '\0', val = get_env_value(shell->env, name));
	if (ptrs[2] == 1)
		app_result(&val);
	if (val)
	{
		ft_strcpy(&result[ptrs[1]], val);
		ptrs[1] += ft_strlen(val);
	}
	else
	{
		result[ptrs[1]++] = '$';
		ft_memcpy(&result[ptrs[1]], name, len);
		ptrs[1] += len;
	}
	ptrs[0] = start + len;
}

static	char	*ft_check_segments(char *seg, t_shell *shell)
{
	int		i;
	bool	has_equal;

	i = 0;
	has_equal = false;
	if (!seg || !shell)
		return (seg);
	while (seg[i])
	{
		if (seg[i] == '=')
		{
			has_equal = true;
			break ;
		}
		if (seg[i] == '$' || seg[i] == '\"' || seg[i] == '\'')
			break ;
		i++;
	}
	if (has_equal && (seg[i] != '$' || seg[i] == '\"' || seg[i] == '\''))
		return (seg);
	return (ft_replace_var3(seg, shell, 1));
}

static	char	*process_token(char *output,
				char *token, t_shell *shell, bool *skip_heredoc)
{
	char	*new_output;
	char	*tmp;

	if (*skip_heredoc)
	{
		new_output = ft_strjoin(output, token);
		*skip_heredoc = false;
	}
	else if (ft_strcmp(token, "<<") == 0)
	{
		new_output = ft_strjoin(output, "<<");
		*skip_heredoc = true;
	}
	else
	{
		tmp = ft_check_segments(token, shell);
		new_output = ft_strjoin(output, tmp);
	}
	return (new_output);
}

char	*process_tokens(char **tokens, t_shell *shell)
{
	size_t	i;
	char	*output;
	bool	skip_heredoc;
	char	*new_output;

	output = ft_strdup("");
	skip_heredoc = false;
	i = 0;
	while (tokens[i])
	{
		output = process_token(output, tokens[i], shell, &skip_heredoc);
		if (tokens[i + 1])
		{
			new_output = ft_strjoin(output, " ");
			output = new_output;
		}
		i++;
	}
	return (output);
}
