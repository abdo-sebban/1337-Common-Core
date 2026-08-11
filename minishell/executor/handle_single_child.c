/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:13:22 by asebban           #+#    #+#             */
/*   Updated: 2025/05/21 12:50:57 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	setup_child_fds_and_redir(t_shell *shell,
				int saved_fds[2])
{
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	if (!handle_redirections_single_child(shell))
		(ft_malloc(0, 0), exit(EXIT_FAILURE));
}

static	void	check_empty_cmd_or_exit(char *cmd)
{
	if (is_cmdline_empty(cmd))
	{
		ft_putstr_fd("minishell: : command not found\n", STDERR_FILENO);
		ft_malloc(0, 0);
		exit(127);
	}
}

static	char	*resolve_cmd_path_or_exit(t_shell *shell, char *cmd)
{
	char		*path;
	char		*path_env;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	path = get_path(shell, true);
	if (!path)
	{
		path_env = get_env_value(shell->env, "PATH");
		if (!path_env)
			return (cmd);
	}
	if (!path)
		err_for_norm();
	return (path);
}

static	void	exec_command_and_cleanup(char *path,
				char **args, t_shell *shell, int saved_fds[2])
{
	char		**env_array;
	struct stat	st;

	env_array = transform_environ_array(shell);
	if (!env_array)
		(ft_malloc(0, 0), exit(126));
	execve(path, args, env_array);
	if (errno == ENOENT || errno == ENOEXEC)
		handle_no_file_error();
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: Is a directory\n", STDERR_FILENO);
		(ft_malloc(0, 0), exit(126));
	}
	try_exec_with_fallback(path, args, env_array, shell);
	perror("minishell");
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
	ft_malloc(0, 0);
	exit(126);
}

void	handle_single_child(t_shell *shell)
{
	char		*path;
	int			saved_fds[2];
	char		*cmd;

	cmd = shell->executor->execs[0];
	setup_child_fds_and_redir(shell, saved_fds);
	check_empty_cmd_or_exit(cmd);
	path = resolve_cmd_path_or_exit(shell, cmd);
	exec_command_and_cleanup(path, shell->executor->execs, shell,
		saved_fds);
}
