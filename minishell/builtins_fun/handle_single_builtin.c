/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:45:27 by asebban           #+#    #+#             */
/*   Updated: 2025/05/21 17:08:39 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	saving_stds(int *stdin_cpy, int *stdout_cpy)
{
	*stdin_cpy = dup(STDIN_FILENO);
	*stdout_cpy = dup(STDOUT_FILENO);
	if (*stdin_cpy == -1 || *stdout_cpy == -1)
		perror("minishell: dup");
}

static	void	execute_builtin(t_shell *shell)
{
	char	**args;
	int		exit_code;

	1 && (args = shell->executor->execs, exit_code = 0);
	if (ft_strcmp(args[0], "pwd") == 0)
		exit_code = pwd(shell->env);
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		exit_code = cd(shell, args);
		if (exit_code == OK)
			exit_code = 0;
		else
			exit_code = 1;
	}
	else if (ft_strcmp(args[0], "env") == 0)
		exit_code = env(shell, args);
	else if (ft_strcmp(args[0], "echo") == 0)
		exit_code = echo(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_code = exit_builtin(shell, args, 0);
	else if (ft_strcmp(args[0], "export") == 0)
		exit_code = export(shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
		exit_code = unset(shell, args);
	exit_status(EXIT_SET, exit_code);
}

static	bool	handle_redirections_single_builtin(t_shell *shell)
{
	t_executor	*exec;

	exec = shell->executor;
	if (exec->fd_in != STDIN_FILENO)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			return (false);
		}
		close(exec->fd_in);
	}
	if (exec->fd_out != STDOUT_FILENO)
	{
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			return (false);
		}
		close(exec->fd_out);
	}
	return (true);
}

static	bool	restore_stds(int stdin_cpy, int stdout_cpy)
{
	bool	success;

	success = true;
	if (dup2(stdin_cpy, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		success = false;
	}
	if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		success = false;
	}
	(close(stdin_cpy), close(stdout_cpy));
	return (success);
}

int	handle_single_builtin(t_shell *shell)
{
	int	stdin_copy;
	int	stdout_copy;

	saving_stds(&stdin_copy, &stdout_copy);
	if (!handle_redirections_single_builtin(shell))
	{
		restore_stds(stdin_copy, stdout_copy);
		return (EXIT_FAILURE);
	}
	execute_builtin(shell);
	restore_stds(stdin_copy, stdout_copy);
	return (EXIT_SUCCESS);
}
