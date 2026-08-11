/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_executor_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:18:37 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 17:56:11 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signals;

t_executor	*fill_executor_list(t_shell *shell, t_executor *list)
{
	t_executor		*current;
	t_lexer_list	*lexer;

	current = list;
	lexer = shell->lex_head;
	while (current)
	{
		list = process_lexemes(list, current, &lexer, shell);
		if (!list)
			return (NULL);
		current = current->next;
	}
	return (list);
}
