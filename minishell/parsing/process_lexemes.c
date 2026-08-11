/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_lexemes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:55:21 by asebban           #+#    #+#             */
/*   Updated: 2025/05/24 21:06:42 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	handle_out_append_node(t_executor *current, t_lexer_list **lexer)
{
	int	ret;

	if (!*lexer || !(*lexer)->next)
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR_FILENO);
		return (FAILED);
	}
	ret = process_out_append(current, *lexer);
	if (ret == FAILED)
		return (FAILED);
	*lexer = (*lexer)->next->next;
	return (0);
}

static	int	handle_in_heredoc_node(t_executor *current,
		t_lexer_list **lexer, t_shell *shell)
{
	int	ret;

	if (!*lexer || !(*lexer)->next)
	{
		ft_putendl_fd("minishell: ambiguous redirect", STDERR_FILENO);
		return (FAILED);
	}
	ret = process_in_heredoc(current, *lexer, shell);
	if (ret == FAILED)
		return (FAILED);
	*lexer = (*lexer)->next->next;
	return (0);
}

static	int	handle_cmd_node(t_executor *current, t_lexer_list **lexer)
{
	int	ret;

	ret = process_command(current, *lexer);
	if (ret == FAILED)
		return (FAILED);
	while (*lexer && (*lexer)->type == CMD)
		*lexer = (*lexer)->next;
	return (0);
}

static int	process_lexeme_segment(t_executor *current,
		t_lexer_list **lexer, t_shell *shell)
{
	while (*lexer && (*lexer)->type != PIPE)
	{
		if ((*lexer)->type == rederect_out || (*lexer)->type == APPEND)
		{
			if (handle_out_append_node(current, lexer) == FAILED)
				return (exit_status(1, 1), FAILED);
			if (current->flag == false)
				exit_status(1, 1);
		}
		else if ((*lexer)->type == REDERECT_IN || (*lexer)->type == HEREDOC)
		{
			if (handle_in_heredoc_node(current, lexer, shell) == FAILED)
				return (FAILED);
			if (current->flag == false)
				exit_status(1, 1);
		}
		else if ((*lexer)->type == CMD)
		{
			if (handle_cmd_node(current, lexer) == FAILED)
				return (exit_status(1, 1), FAILED);
		}
		else
			*lexer = (*lexer)->next;
	}
	return (0);
}

t_executor	*process_lexemes(t_executor *list,
		t_executor *current, t_lexer_list **lexer, t_shell *shell)
{
	if (process_lexeme_segment(current, lexer, shell) == FAILED)
		return (NULL);
	if (*lexer && (*lexer)->type == PIPE)
		*lexer = (*lexer)->next;
	return (list);
}
