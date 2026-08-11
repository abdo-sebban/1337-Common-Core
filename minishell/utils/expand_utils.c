/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:24:39 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 10:51:44 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	parse_var_name(const char *str, char **out_var)
{
	size_t	j;

	j = 1;
	while (str[j]
		&& (ft_isalnum((unsigned char)str[j]) || str[j] == '_'))
		j++;
	*out_var = ft_strndup(str + 1, j - 1);
	return (j);
}

char	*expand_present_var(const char *trimmed, t_shell *shell)
{
	char	*result;

	result = ft_replace_var3(trimmed, shell, 1);
	return (result);
}

char	*expand_absent_var(const char *trimmed,
		size_t var_len, t_shell *shell)
{
	const char	*next;

	next = skip_leading_spaces(trimmed + var_len);
	if (ft_strncmp(next, "echo", 4) == 0)
		return (change_all_var(next, shell));
	if (ft_strncmp(next, "export", 6) != 0)
		return (expand_present_var(trimmed, shell));
	return (NULL);
}

char	*expand_vars_in(const char *src, t_shell *shell)
{
	const char	*trimmed;
	char		*first_var;
	size_t		var_len;
	char		*first_val;

	trimmed = skip_leading_spaces(src);
	first_var = NULL;
	first_val = NULL;
	var_len = 0;
	if (*trimmed == '$')
	{
		var_len = parse_var_name(trimmed, &first_var);
		first_val = get_env_value(shell->env, first_var);
	}
	if (first_val)
		return (expand_present_var(trimmed, shell));
	else
		return (expand_absent_var(trimmed, var_len, shell));
}

char	*process_single_chunk(char *chunk, t_shell *shell)
{
	char	*trimmed;
	char	*expanded;

	trimmed = (char *)skip_leading_spaces(chunk);
	if (ft_strncmp(trimmed, "echo", 4) == 0)
	{
		expanded = change_all_var(chunk, shell);
		if (expanded)
			return (expanded);
	}
	if (ft_strncmp(trimmed, "export", 6) != 0)
	{
		expanded = expand_vars_in(trimmed, shell);
		if (expanded)
			return (expanded);
	}
	return (chunk);
}
