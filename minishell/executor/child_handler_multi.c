/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handler_multi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:38:38 by asebban           #+#    #+#             */
/*   Updated: 2025/05/21 21:21:38 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	handle_redirections_pipeline(int *pipefd, t_executor *cur)
{
	if (cur->fd_in != STDIN_FILENO && cur->fd_in >= 0)
	{
		if (dup2(cur->fd_in, STDIN_FILENO) == -1)
			return (FAIL_SYSCALL);
		close(cur->fd_in);
	}
	if (cur->fd_out != STDOUT_FILENO && cur->fd_out >= 0)
	{
		if (dup2(cur->fd_out, STDOUT_FILENO) == -1)
			return (FAIL_SYSCALL);
		close(cur->fd_out);
	}
	if (pipefd[0] >= 0)
		close(pipefd[0]);
	if (pipefd[1] >= 0)
		close(pipefd[1]);
	return (OKAY);
}

static void	err(int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
		ft_malloc(0, 0);
		exit(127);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("minishell: Is a directory\n", STDERR_FILENO);
		ft_malloc(0, 0);
		exit(126);
	}
	else if (flag == 3)
	{
		ft_putstr_fd("minishell: Permission denied\n", STDERR_FILENO);
		(ft_malloc(0, 0), exit(126));
	}
}

void	execute_other(t_executor *current, t_info *info)
{
	char		*path;
	char		**env_array;
	struct stat	st;

	path = execute_other_helper(current);
	if (!path)
		err(1);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		err(2);
	env_array = transform_environ_array(info->shell);
	if (!env_array)
		(ft_malloc(0, 0), exit(126));
	execve(path, current->execs, env_array);
	if (errno == ENOENT || errno == ENOEXEC)
		handle_no_file_error();
	try_exec_with_fallback(path, current->execs, env_array, info->shell);
	if (errno == EACCES)
		err(3);
	else
	{
		perror("minishell");
		(ft_malloc(0, 0), exit(126));
	}
}

static	void	execute_builtin_child(t_info *info, t_executor *cur)
{
	int		exit_code;
	char	**args;

	args = cur->execs;
	exit_code = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		exit_code = echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		exit_code = cd(info->shell, args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		exit_code = pwd(info->shell->env);
	else if (ft_strcmp(args[0], "export") == 0)
		exit_code = export(info->shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		exit_code = unset(info->shell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		exit_code = env(info->shell, args);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_code = exit_builtin(info->shell, args, 1);
	ft_malloc(0, 0);
	exit_status(1, exit_code);
	exit(exit_code);
}

int	child_handler_multi(int *fildes, t_executor *current, t_info *info)
{
	if (!current || !current->execs || !current->execs[0] || !current->flag)
	{
		ft_malloc(0, 0);
		return (FAIL_SYSCALL_CHILD);
	}
	if (handle_redirections_pipeline(fildes, current) == FAIL_SYSCALL)
		(ft_malloc(0, 0), exit(FAIL_SYSCALL_CHILD));
	if (is_cmdline_empty(current->execs[0]))
	{
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
		(ft_malloc(0, 0), exit(127));
	}
	if (is_builtin(current->execs[0]))
		execute_builtin_child(info, current);
	else
		execute_other(current, info);
	return (FAIL_SYSCALL_CHILD);
}
