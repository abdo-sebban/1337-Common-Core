/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:41:02 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 12:13:18 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = validate_and_get_path(s_cmd, env);
	if (!path)
	{
		ft_putstr_fd("\033[31mpipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		if ((s_cmd[0][0] == '.' && s_cmd[0][1] == '/') || s_cmd[0][0] == '/')
		{
			perror("pipex");
		}
		else
			(ft_putstr_fd("\033[31mpipex: command not found: ", 2),
				ft_putendl_fd(s_cmd[0], 2));
		(free(path), ft_free_tab(s_cmd), exit(127));
	}
}

static	void	child1(char **av, int *p_fd, char **env)
{
	int	fd;

	access_infile(av[1], p_fd);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_error(p_fd);
	if (dup2(fd, 0) == -1)
		(close(fd), exit_error(p_fd));
	if (dup2(p_fd[1], 1) == -1)
		(close(fd), exit_error(p_fd));
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exec(av[2], env);
}

static	void	child2(char **av, int *p_fd, char **env)
{
	int	fd;

	access_outfile(av[4], p_fd);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(p_fd);
	if (dup2(p_fd[0], 0) == -1)
		(close(fd), exit_error(p_fd));
	if (dup2(fd, 1) == -1)
		(close(fd), exit_error(p_fd));
	close(fd);
	close(p_fd[0]);
	close(p_fd[1]);
	exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		usage_pipex();
	if (pipe(p_fd) == -1)
		exit_error(p_fd);
	pid1 = fork();
	if (pid1 == -1)
		exit_error(p_fd);
	if (pid1 == 0)
		child1(av, p_fd, env);
	pid2 = fork();
	if (pid2 == -1)
		exit_error(p_fd);
	if (pid2 == 0)
		child2(av, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
