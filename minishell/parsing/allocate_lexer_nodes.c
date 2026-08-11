/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_lexer_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:07:42 by asebban           #+#    #+#             */
/*   Updated: 2025/05/16 12:29:15 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_lexer_list	*create_new_node(void)
{
	t_lexer_list	*node;

	node = (t_lexer_list *)ft_malloc(sizeof(t_lexer_list), 1);
	if (node)
		node->prev = NULL;
	return (node);
}

static void	clear_lexer_nodes(t_lexer_list *head)
{
	t_lexer_list	*tmp;

	while (head)
	{
		tmp = head->next;
		head = tmp;
	}
}

static t_lexer_list	*append_lexer_nodes(t_lexer_list *head, int size)
{
	t_lexer_list	*current;
	t_lexer_list	*prev;
	int				i;

	prev = head;
	i = 1;
	while (i < size)
	{
		current = create_new_node();
		if (!current)
		{
			clear_lexer_nodes(head);
			return (NULL);
		}
		current->prev = prev;
		prev->next = current;
		prev = current;
		i++;
	}
	if (size > 0)
		prev->next = NULL;
	return (head);
}

t_lexer_list	*allocate_lexer_nodes(int size)
{
	t_lexer_list	*head;

	if (size == 0)
		return (NULL);
	head = create_new_node();
	if (!head)
		return (NULL);
	return (append_lexer_nodes(head, size));
}
