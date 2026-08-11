/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:14:41 by asebban           #+#    #+#             */
/*   Updated: 2025/05/21 17:23:59 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_fornorm(char **input)
{
	while (**input == ' ' || **input == '\t')
		(*input)++;
	if (**input == '|')
		return (0);
	return (1);
}

int	skip_quates(char **input)
{
	char	quote;

	if (**input == '\0' || (**input != '\'' && **input != '"'))
		return (0);
	quote = **input;
	(*input)++;
	while (**input && **input != quote)
		(*input)++;
	if (**input == quote)
	{
		(*input)++;
		return (1);
	}
	return (0);
}

static	int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static	char	*get_last_heredoc_delimiter(const char *cmdline)
{
	char	*last;
	size_t	i;
	size_t	start;
	size_t	len;

	1 && (i = 0, last = NULL);
	while (cmdline[i])
	{
		if (cmdline[i] == '<' && cmdline[i + 1] == '<')
		{
			i += 2;
			while (cmdline[i] && ft_isspace(cmdline[i]))
				++i;
			start = i;
			while (cmdline[i] && !ft_isspace(cmdline[i])
				&& cmdline[i] != '<' && cmdline[i] != '>' && cmdline[i] != '|')
				++i;
			len = i - start;
			if (len > 0)
				last = ft_strndup(cmdline + start, len);
		}
		else
			i++;
	}
	return (last);
}

int	is_last_delim_quoted(const char *cmdline)
{
	char	*raw;
	int		quoted;

	raw = get_last_heredoc_delimiter(cmdline);
	if (!raw)
		return (0);
	quoted = (ft_strchr(raw, '\'') != NULL || ft_strchr(raw, '"') != NULL);
	return (quoted);
}
