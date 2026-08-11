/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:02:22 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 13:25:46 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_environ_node	*create_environ_node(char *var)
{
	t_environ_node	*new_node;
	char			*equal_sign;
	size_t			key_len;

	if (!var)
		return (NULL);
	new_node = (t_environ_node *)ft_malloc(sizeof(t_environ_node), 1);
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		key_len = equal_sign - var;
		new_node->key = ft_substr(var, 0, key_len);
		new_node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new_node->key = ft_strdup(var);
		new_node->value = NULL;
	}
	if (!new_node->key || (equal_sign && !new_node->value))
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

t_environ_node	*add_back_environ_node(t_environ_list *env,
				t_environ_node *node)
{
	t_environ_node	*current;

	if (!env || !node)
		return (NULL);
	if (!env->head)
	{
		env->head = node;
		env->size = 1;
		return (node);
	}
	current = env->head;
	while (current->next)
		current = current->next;
	current->next = node;
	env->size++;
	return (node);
}

t_environ_node	*get_node(t_environ_list *env, char *key)
{
	t_environ_node	*current;

	if (!env || !key)
		return (NULL);
	current = env->head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
