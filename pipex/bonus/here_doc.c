/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:19:38 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 12:52:04 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static	void	pipe_herdoc(char *limiter, int *fd, int ac)
{
	char	*line;
	int		i;

	while (1)
	{
		i = 0;
		while (i++ < ac - 4)
			write(1, "pipe ", 6);
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (!line)
			(close(fd[1]), exit(1));
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			close(fd[1]);
			exit(0);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
}

void	here_doc(char *limiter, int argc)
{
	pid_t	pid;
	int		fd[2];

	if (argc < 6)
		usage_pipex_bonus();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		(close(fd[1]), close(fd[0]), error());
	else if (pid == 0)
	{
		close(fd[0]);
		pipe_herdoc(limiter, fd, argc);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			(close(fd[0]), error());
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}
