/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:42:22 by asebban           #+#    #+#             */
/*   Updated: 2025/05/10 10:51:46 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*build_full_str(const t_environ_node *node)
{
	char	*joined;
	char	*full;

	if (node->value)
	{
		joined = ft_strjoin(node->key, "=");
		full = ft_strjoin(joined, node->value);
	}
	else
		full = ft_strdup(node->key);
	return (full);
}

void	insert_sorted(t_environ_node **sorted, t_environ_node *new_node)
{
	t_environ_node	*current;

	if (!*sorted || ft_strcmp(new_node->key, (*sorted)->key) < 0)
	{
		new_node->next = *sorted;
		*sorted = new_node;
	}
	else
	{
		current = *sorted;
		while (current->next
			&& ft_strcmp(new_node->key, current->next->key) > 0)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}

t_environ_node	*create_sorted_copy(const t_environ_list *env_list)
{
	t_environ_node	*tmp;
	t_environ_node	*sorted;
	char			*full;
	t_environ_node	*copy;

	tmp = env_list->head;
	sorted = NULL;
	while (tmp)
	{
		full = build_full_str(tmp);
		copy = create_environ_node(full);
		if (!copy)
			return (NULL);
		insert_sorted(&sorted, copy);
		tmp = tmp->next;
	}
	return (sorted);
}

void	print_sorted_nodes(const t_environ_node *sorted)
{
	const t_environ_node	*cur;

	cur = sorted;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else
			printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
}

void	print_sorted_env(t_environ_list *env)
{
	t_environ_node	*sorted;

	sorted = create_sorted_copy(env);
	if (!sorted)
		return ;
	print_sorted_nodes(sorted);
}
