/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:52:33 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 22:17:08 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_redirections(t_executor *cur)
{
	if (!cur)
		return ;
	if (cur->fd_in != STDIN_FILENO)
	{
		close(cur->fd_in);
		cur->fd_in = STDIN_FILENO;
	}
	if (cur->fd_out != STDOUT_FILENO)
	{
		close(cur->fd_out);
		cur->fd_out = STDOUT_FILENO;
	}
}

int	err_red(t_executor *cur)
{
	ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
	exit_status(1, 1);
	if (cur->size == 1)
		return (FAILED);
	return (OK);
}
