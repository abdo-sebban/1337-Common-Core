/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:32:39 by asebban           #+#    #+#             */
/*   Updated: 2025/05/21 13:17:23 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	delete_variable(t_shell *shell, char *arg)
{
	t_environ_node	*current;
	t_environ_node	*prev;

	prev = NULL;
	current = shell->env->head;
	while (current)
	{
		if (ft_strcmp(current->key, arg) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env->head = current->next;
			shell->env->size--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static	void	unset_arg(t_shell *shell, char *arg)
{
	delete_variable(shell, arg);
}

int	unset(t_shell *shell, char **args)
{
	int	i;

	if (!args[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "PWD") == 0)
		{
			if (get_env_value(shell->env, "PWD"))
				save_pwd(1, get_env_value(shell->env, "PWD"));
		}
		unset_arg(shell, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
