/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:04 by asebban           #+#    #+#             */
/*   Updated: 2025/05/24 20:52:19 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_token	get_token_type(const char *s, int is_op)
{
	if (!is_op)
		return (CMD);
	if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(s, ">") == 0)
		return (rederect_out);
	if (ft_strcmp(s, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(s, "<") == 0)
		return (REDERECT_IN);
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	return (CMD);
}

static	t_lexer_list	*create_node(t_split *sp)
{
	t_lexer_list	*node;

	node = ft_malloc(sizeof(*node), 1);
	if (!node)
		return (NULL);
	node->str = sp->str;
	node->type = get_token_type(sp->str, sp->is_operator);
	node->next = NULL;
	return (node);
}

static	void	check_heredoc_limit(t_lexer_list *node)
{
	if (node->type == HEREDOC)
		count_herdoc(1);
	if (count_herdoc(0) == 16)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		ft_malloc(0, 0);
		exit(2);
	}
}

static	void	append_node(t_lexer_list **head,
		t_lexer_list **tail, t_lexer_list *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

t_lexer_list	*tokenize(t_shell *shell)
{
	t_split			*splits;
	t_lexer_list	*head;
	t_lexer_list	*tail;
	t_lexer_list	*node;
	t_split			*sp;

	if (!shell || !shell->rl_copy)
		return (NULL);
	1 && (head = NULL, tail = NULL);
	splits = ft_newsplit(shell->rl_copy);
	if (!splits)
		return (NULL);
	count_herdoc(2);
	sp = splits;
	while (sp)
	{
		node = create_node(sp);
		if (!node)
			break ;
		check_heredoc_limit(node);
		append_node(&head, &tail, node);
		sp = sp->next;
	}
	return (head);
}
