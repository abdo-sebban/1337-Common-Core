/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:57:24 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 11:36:52 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/pipex_bonus.h"

char	*validate_and_get_path(char **command, char **envp)
{
	char	*path;

	if (command[0][0] == '.' && command[0][1] == '/' )
		path = ft_strdup(command[0]);
	else if (command[0][0] == '/')
		path = ft_strdup(command[0]);
	else
		path = get_path(command[0], envp);
	if (!path)
	{
		write(2, "Error: Command not found : ", 27);
		ft_putstr_fd(command[0], 2);
		exit(127);
	}
	return (path);
}

static	char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

static	void	command_not_found(char **s_cmd)
{
	ft_putstr_fd("\033[31mpipex: command not found: ", 2);
	ft_putendl_fd(s_cmd[0], 2);
	ft_free_tab(s_cmd);
	exit(-1);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(get_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		command_not_found(s_cmd);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab(s_cmd), exec);
		free(exec);
	}
	(ft_free_tab(allpath), ft_free_tab(s_cmd));
	return (cmd);
}
