/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:21:28 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 13:51:06 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

const char	*skip_leading_spaces(const char *s)
{
	while (*s && ft_isspace((unsigned char)*s))
		s++;
	return (s);
}

static	char	*join_with_pipes(char **parts)
{
	char	*res;
	size_t	i;

	res = NULL;
	i = 0;
	while (parts[i])
	{
		if (!res)
			res = ft_strdup(parts[i]);
		else
			res = ft_strjoin(ft_strjoin(res, "|"), parts[i]);
		i++;
	}
	return (res);
}

static	int	has_heredoc(const char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '<' && str[j + 1] == '<')
			return (1);
		j++;
	}
	return (0);
}

char	*process_line_expand_first_var(char *line, t_shell *shell)
{
	char	**parts;
	size_t	i;
	char	*result;
	int		skip_herdoc;

	parts = ft_split1(line, '|');
	if (!parts)
		return (NULL);
	i = 0;
	while (parts[i])
	{
		skip_herdoc = 0;
		skip_herdoc = has_heredoc(parts[i]);
		if (!skip_herdoc)
			parts[i] = process_single_chunk(parts[i], shell);
		i++;
	}
	result = join_with_pipes(parts);
	return (result);
}
