/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:23:41 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 17:44:58 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_too_many(int arg_count, int in_pipe)
{
	if (arg_count > 2)
	{
		exit_status(1, 127);
		if (!in_pipe)
			ft_putstr_fd("exit\nminishell: exit\
: too many arguments\n", STDERR_FILENO);
		else
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (-1);
}
