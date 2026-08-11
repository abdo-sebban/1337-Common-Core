/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:40:32 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 12:54:02 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	check_file_access(char *file, int mode)
{
	if (mode == 0)
	{
		if (access(file, F_OK) == -1 || access(file, R_OK) == -1)
		{
			perror("pipex");
			exit(1);
		}
	}
	else
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		{
			perror("pipex");
			exit(1);
		}
	}
}

static void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
	{
		ft_putstr_fd("\033[31mpipex: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(127);
	}
	path = get_path(s_cmd[0], env);
	if (!path)
	{
		ft_putstr_fd("\033[31mpipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		perror("pipex");
		ft_free_tab(s_cmd);
		exit(127);
	}
}

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		(close(fd[1]), close(fd[0]), error());
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			(close(fd[1]), error());
		exec(argv, envp);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			(close(fd[0]), error());
		waitpid(pid, NULL, 0);
	}
}

void	check_file_and_open(char **av, int ac, int *filein, int *fileout)
{
	check_file_access(av[1], 0);
	check_file_access(av[ac - 1], 1);
	*filein = open_file(av[1], 2);
	if (*filein == -1)
		error();
	*fileout = open_file(av[ac - 1], 1);
	if (*fileout == -1)
		(close(*filein), error());
	if (dup2(*filein, STDIN_FILENO) == -1)
		(close(*filein), close(*fileout), error());
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		filein;
	int		fileout;

	if (ac >= 5)
	{
		if (ft_strcmp(av[1], "here_doc") == 0)
		{
			i = 3;
			here_doc(av[2], ac);
			fileout = open_file(av[ac - 1], 0);
		}
		else
		{
			i = 2;
			check_file_and_open(av, ac, &filein, &fileout);
		}
		while (i < ac - 2)
			child_process(av[i++], env);
		if (dup2(fileout, STDOUT_FILENO) == -1)
			(close(filein), close(fileout), error());
		exec(av[ac - 2], env);
		return (0);
	}
	usage_pipex_bonus();
}
