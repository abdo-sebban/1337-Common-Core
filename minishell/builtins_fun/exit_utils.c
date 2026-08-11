/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:52 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 11:26:49 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_exit(t_shell *shell, int exit_code)
{
	(void)shell;
	ft_malloc(0, 0);
	exit(exit_code);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	print_exit_if_needed(int in_pipe)
{
	if (!in_pipe)
		printf("exit\n");
}

void	handle_no_args(t_shell *shell, int exit_code,
		int arg_count, int in_pipe)
{
	if (arg_count == 1)
	{
		print_exit_if_needed(in_pipe);
		clean_exit(shell, exit_code);
	}
}

int	handle_non_numeric(char *arg, t_shell *shell, int in_pipe)
{
	(void)arg;
	print_exit_if_needed(in_pipe);
	ft_putstr_fd("minishell: numeric argument required\n", STDERR_FILENO);
	clean_exit(shell, 2);
	return (2);
}
