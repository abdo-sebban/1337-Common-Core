/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_builtin2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:34:20 by asebban           #+#    #+#             */
/*   Updated: 2025/05/13 12:26:18 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(char *exec)
{
	if (!exec)
		return (false);
	return (ft_strcmp(exec, "echo") == 0
		|| ft_strcmp(exec, "cd") == 0
		|| ft_strcmp(exec, "pwd") == 0
		|| ft_strcmp(exec, "export") == 0
		|| ft_strcmp(exec, "unset") == 0
		|| ft_strcmp(exec, "env") == 0
		|| ft_strcmp(exec, "exit") == 0);
}
