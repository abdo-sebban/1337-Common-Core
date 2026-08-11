/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:58:23 by asebban           #+#    #+#             */
/*   Updated: 2025/05/24 21:08:18 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	open_outputfile(t_executor *current, t_lexer_list *lexer)
{
	int	new_fd;

	if (!lexer || !lexer->str || lexer->type != 1)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		exit_status(1, 1);
		if (current->size == 1)
			return (false);
		return (current->flag = false, true);
	}
	if (current->append)
		new_fd = open(lexer->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		new_fd = open(lexer->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd == -1)
	{
		(perror(lexer->str), cleanup_redirections(current));
		if (current->size == 1)
			return (false);
		return (current->flag = false, true);
	}
	if (current->fd_out != STDOUT_FILENO)
		close(current->fd_out);
	current->fd_out = new_fd;
	return (true);
}

int	process_out_append(t_executor *current, t_lexer_list *lexer)
{
	current->append = (lexer->type == APPEND);
	current->rederect_out = (lexer->type == rederect_out);
	if (!open_outputfile(current, lexer->next))
		return (FAILED);
	return (OK);
}

static	int	open_input_fd(t_lexer_list *lex, t_shell *sh)
{
	int	new_fd;

	if (lex->type == HEREDOC)
	{
		new_fd = create_heredoc(lex->next->str, sh);
		return (new_fd);
	}
	return (open(lex->next->str, O_RDONLY));
}

int	process_in_heredoc(t_executor *cur, t_lexer_list *lex, t_shell *sh)
{
	int	new_fd;

	if (!lex->next || !lex->next->str || lex->next->type != 1)
		return (err_red(cur));
	new_fd = open_input_fd(lex, sh);
	if (lex->type == HEREDOC && (new_fd == -1 || new_fd == -2))
	{
		if (new_fd > 0)
			close(new_fd);
		if (cur->fd_in != STDIN_FILENO)
			close(cur->fd_in);
		exit_status(1, 130);
		return (FAILED);
	}
	if (lex->type != HEREDOC && new_fd == -1)
	{
		(perror(lex->next->str), cleanup_redirections(cur));
		exit_status(1, 1);
		if (cur->size == 1)
			return (FAILED);
		return (cur->flag = false, OK);
	}
	if (cur->fd_in != STDIN_FILENO)
		close(cur->fd_in);
	return ((cur->fd_in = new_fd), OK);
}

int	process_command(t_executor *current, t_lexer_list *lexer)
{
	int				size;
	t_lexer_list	*tmp;
	int				i;

	i = 0;
	size = 0;
	tmp = lexer;
	while (tmp && tmp->type == CMD)
	{
		size++;
		tmp = tmp->next;
	}
	current->execs = (char **)ft_malloc((size + 2) * sizeof(char *), 1);
	if (!current->execs)
		return (FAILED);
	while (i < size)
	{
		current->execs[i] = ft_strdup(lexer->str);
		if (!current->execs[i])
			return (FAILED);
		lexer = lexer->next;
		i++;
	}
	current->execs[i] = NULL;
	return (OK);
}
