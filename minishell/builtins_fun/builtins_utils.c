/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:39:36 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/13 14:13:48 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*save_pwd(int action, char *value)
{
	static char	*save;

	if (action == 0)
		return (save);
	else if (action == 1)
	{
		if (value)
			save = ft_strdup(value);
		else
			save = NULL;
	}
	return (save);
}

t_environ_node	*ft_getenv(t_environ_list *env, char *key)
{
	t_environ_node	*current;

	current = env->head;
	while (current)
	{
		if (current->key && !ft_strcmp(current->key, key))
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	export_no_args(t_shell *shell)
{
	print_sorted_env(shell->env);
	return (EXIT_SUCCESS);
}

bool	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str || ft_isdigit(str[0]) || str[0] == '=' || str[0] == '$')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (true);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
