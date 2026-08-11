/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:31:19 by asebban           #+#    #+#             */
/*   Updated: 2025/05/19 12:06:35 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_info	*init_info(t_shell *shell)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	info->shell = shell;
	info->stdin_copy = dup(STDIN_FILENO);
	info->pids = (pid_t *)ft_calloc(shell->executor->size, sizeof(pid_t));
	if (!info->pids)
		return (NULL);
	return (info);
}

void	wait_pipeline(t_info *info, int number)
{
	int	status;
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < number)
	{
		waitpid(info->pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_status(EXIT_SET, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (status == 131 && j == 0)
				(printf("Quit (core dumped)\n"), j = 1);
			else if (status == 2 && j == 0)
				(printf("\n"), j = 1);
			exit_status(EXIT_SET, 128 + WTERMSIG(status));
		}
		i++;
	}
	if (info->stdin_copy != STDIN_FILENO)
		(dup2(info->stdin_copy, STDIN_FILENO), close(info->stdin_copy));
}

static	void	handle_pipe(int *fildes, t_executor *current)
{
	if (pipe(fildes) == -1)
	{
		perror("minishell: pipe");
		exit_status(EXIT_SET, 1);
		return ;
	}
	if (current->fd_out == STDOUT_FILENO || isatty(current->fd_out))
		current->fd_out = fildes[1];
	else
		close(fildes[1]);
	if (current->next->fd_in == STDIN_FILENO)
		current->next->fd_in = fildes[0];
	else
		close(fildes[0]);
}

static	void	handle_fork(t_info *info, t_executor *current, int *fildes)
{
	int	ret;

	info->pids[current->id] = fork();
	if (info->pids[current->id] == -1)
	{
		perror("minishell: fork");
		exit_status(EXIT_SET, 1);
		return ;
	}
	else if (info->pids[current->id] == 0)
	{
		signal_setup(3);
		ret = child_handler_multi(fildes, current, info);
		ft_malloc(0, 0);
		exit(ret);
	}
}

void	handle_multi(t_info *info, t_executor *current)
{
	int	fildes[2];

	fildes[0] = -1;
	fildes[1] = -1;
	if (current->next)
		handle_pipe(fildes, current);
	handle_fork(info, current, fildes);
	if (current->fd_in != STDIN_FILENO)
		close(current->fd_in);
	if (current->fd_out != STDOUT_FILENO)
		close(current->fd_out);
}
