/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:20:59 by asebban           #+#    #+#             */
/*   Updated: 2025/05/24 20:35:20 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_split	*ft_newsplit(const char *s)
{
	t_split	*head;
	t_split	*tail;
	t_split	*node;
	int		idx[2];
	char	*tok;

	1 && (idx[0] = 0, idx[1] = 0);
	1 && (head = NULL, tail = NULL, node = NULL);
	if (!s)
		return (NULL);
	tok = get_next_token(s, &idx[0], &idx[1]);
	while (tok)
	{
		node = ft_malloc(sizeof(*node), 1);
		if (!node)
			break ;
		1 && (node->str = tok, node->is_operator = idx[1]);
		node->next = NULL;
		if (!head)
			head = node;
		else
			tail->next = node;
		1 && (tail = node, tok = get_next_token(s, &idx[0], &idx[1]));
	}
	return (head);
}
