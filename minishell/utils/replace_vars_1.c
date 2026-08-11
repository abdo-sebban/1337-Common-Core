/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:02:15 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 11:01:41 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_variable(const char *segment,
	char **res, int *i, t_shell *shell)
{
	handle_expand_variable(segment, res, i, shell);
}

char	*segment_expand(const char *segment, t_shell *shell)
{
	char	*res;
	int		i;
	int		in_squote;
	int		skip_word;

	1 && (res = ft_strdup(""), i = 0, in_squote = 0, skip_word = 0);
	while (segment[i])
	{
		if (should_toggle_squote(segment[i], skip_word))
			in_squote = !in_squote;
		if (!in_squote && segment[i] == '<' && segment[i + 1] == '<')
			skip_word = handle_skip_heredoc(segment, &res, &i);
		else if (skip_word)
			process_skip_word(segment, &res, &i, &skip_word);
		else if (!in_squote && segment[i] == '$' && (!ft_isalnum(segment[i + 1])
				&& segment[i + 1] != '_' && segment[i + 1] != '?'))
			1 && (append_char(&res, "$", 1), i += 1);
		else if (!in_squote && segment[i] == '$')
			process_variable(segment, &res, &i, shell);
		else
			1 && (append_char(&res, &segment[i], 1), i++);
	}
	return (res);
}

char	*process_export_segment(const char *seg, t_shell *shell)
{
	char	**parts;
	char	*ret;
	char	*value_expanded;

	if (ft_strncmp(seg, "export ", 7))
		return (ft_strdup(seg));
	parts = ft_split(seg + 7, '=');
	if (!parts || !parts[0])
		return (ft_strdup(seg));
	if (!parts[1])
	{
		ret = ft_strjoin(ft_strjoin("export ", parts[0]), "=\"\"");
		return (ret);
	}
	value_expanded = segment_expand(parts[1], shell);
	ret = ft_strjoin(ft_strjoin("export ", parts[0]), "=\"");
	ret = ft_strjoin(ft_strjoin(ret, value_expanded), "\"");
	return (ret);
}

char	*expand_variables(const char *input, t_shell *shell)
{
	char	**segs;
	char	*joined;
	int		i;
	char	*part;

	i = 0;
	segs = ft_split(input, '|');
	if (!segs)
		return (ft_strdup(input));
	joined = NULL;
	while (segs[i])
	{
		part = process_export_segment(ft_strtrim1(segs[i]), shell);
		if (joined)
			joined = ft_strjoin(ft_strjoin(joined, " | "), part);
		else
			joined = ft_strdup(part);
		i++;
	}
	return (joined);
}
