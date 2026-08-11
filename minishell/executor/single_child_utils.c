/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_child_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:02:46 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 17:50:49 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	handle_redirections_single_child(t_shell *shell)
{
	if (shell->executor->fd_in != STDIN_FILENO)
	{
		if (dup2(shell->executor->fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 input redirection failed");
			return (false);
		}
		close(shell->executor->fd_in);
	}
	if (shell->executor->fd_out != STDOUT_FILENO)
	{
		if (dup2(shell->executor->fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 output redirection failed");
			return (false);
		}
		close(shell->executor->fd_out);
	}
	return (true);
}

static	char	*get_env1_value(t_shell *shell, const char *key)
{
	t_environ_node	*env;
	size_t			key_len;

	if (!shell || !shell->env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	env = shell->env->head;
	while (env)
	{
		if (ft_strncmp(env->key, key, key_len) == 0
			&& env->key[key_len] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static	char	*find_in_path_dirs(char **dirs, const char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		if (dirs[i][0] == '\0' ||
			(dirs[i][0] == '.' && dirs[i][1] == '\0'))
		{
			i++;
			continue ;
		}
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			break ;
		full_path = ft_strjoin(tmp, cmd);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

static	char	*get_absolute_path(t_shell *shell)
{
	char	*path_var;
	char	**path_dirs;
	char	*result;

	if (!shell->executor->execs[0])
		return (NULL);
	path_var = get_env1_value(shell, "PATH");
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	result = find_in_path_dirs(path_dirs, shell->executor->execs[0]);
	return (result);
}

char	*get_path(t_shell *shell, bool printerror)
{
	char	*path;

	if (!shell->executor->execs || !shell->executor->execs[0])
		return (NULL);
	if (ft_strchr((shell->executor->execs[0]), '/'))
	{
		path = ft_strdup(shell->executor->execs[0]);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == -1 && printerror)
			return (get_path_error(), NULL);
		return (path);
	}
	path = get_absolute_path(shell);
	if (!path)
		return (NULL);
	if (access(path, F_OK) == -1 && printerror)
		return (get_path_error(), NULL);
	return (path);
}
