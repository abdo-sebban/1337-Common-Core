/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:47:57 by asebban           #+#    #+#             */
/*   Updated: 2025/05/06 18:16:03 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	**get_path_array(t_environ_list *env)
{
	t_environ_node	*path_node;
	char			**path_array;
	char			*path_value;

	path_node = get_node(env, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	path_value = ft_strdup(path_node->value);
	if (!path_value)
		return (NULL);
	path_array = ft_split(path_value, ':');
	if (!path_array)
		return (NULL);
	return (path_array);
}

void	set_path_executor(t_executor *list, t_environ_list *env)
{
	char		**path_array;
	t_executor	*current;

	path_array = get_path_array(env);
	current = list;
	while (current)
	{
		current->path = path_array;
		current = current->next;
	}
}
