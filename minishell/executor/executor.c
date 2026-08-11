/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:42:43 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 20:00:21 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	handle_builtin_or_return(t_shell *shell, t_executor *cur)
{
	if (!cur || !cur->execs || !cur->execs[0])
	{
		if (cur)
		{
			if (cur->fd_in != STDIN_FILENO)
				close(cur->fd_in);
			if (cur->fd_out != STDOUT_FILENO)
				close(cur->fd_out);
		}
		exit_status(EXIT_SET, 0);
		return ;
	}
	if (is_builtin(cur->execs[0]))
	{	
		if (handle_single_builtin(shell) == EXIT_FAILURE)
			exit_status(EXIT_SET, 1);
	}
}

static	void	handle_fork_execution(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		cleanup_redirections(shell->executor);
		(perror("minishell"), exit_status(EXIT_SET, 1));
		return ;
	}
	if (pid == 0)
		(signal_setup(3), handle_single_child(shell));
	waitpid(pid, &status, 0);
	cleanup_redirections(shell->executor);
	if (WIFEXITED(status))
		exit_status(EXIT_SET, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (status == 131)
			(printf("Quit (core dumped)\n"), exit_status(EXIT_SET, 131));
		else if (status == 2)
			(printf("\n"), exit_status(EXIT_SET, 128 + WTERMSIG(status)));
	}
	else
		exit_status(EXIT_SET, 1);
}

static	void	handle_single(t_shell *shell)
{
	t_executor	*cur;

	cur = shell->executor;
	if (!cur || !cur->execs || !cur->execs[0])
	{
		if (cur)
		{
			if (cur->fd_in != STDIN_FILENO)
				close(cur->fd_in);
			if (cur->fd_out != STDOUT_FILENO)
				close(cur->fd_out);
		}
		return ;
	}
	cur = shell->executor;
	handle_builtin_or_return(shell, cur);
	if (!is_builtin(cur->execs[0]))
		handle_fork_execution(shell);
}

void	executor(t_shell *shell)
{
	t_executor	*current;
	t_info		*info;

	current = shell->executor;
	if (!current)
		return ;
	if (current->size == 1)
		handle_single(shell);
	else
	{
		info = init_info(shell);
		if (!info)
			return ;
		while (current)
		{
			handle_multi(info, current);
			current = current->next;
		}
		wait_pipeline(info, shell->executor->size);
	}
}
