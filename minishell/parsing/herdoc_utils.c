/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:39:43 by asebban           #+#    #+#             */
/*   Updated: 2025/05/19 10:04:04 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_heredoc_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return (-1);
	return (0);
}

void	handle_eof(void)
{
	ft_putstr_fd("minishell: warning: here-document \
delimited by end-of-file\n", STDERR_FILENO);
}

bool	is_delimiter(const char *line, const char *delimiter)
{
	return (line && ft_strcmp(line, delimiter) == 0);
}
