/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:27:05 by asebban           #+#    #+#             */
/*   Updated: 2025/05/24 20:20:34 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip(char	**input, int j)
{
	if (j > 2)
		return (write(2, "minishell: syntax error !!\n", 28), 0);
	while (**input && (**input == ' ' || **input == '\t'))
		(*input)++;
	if (ft_special(**input, 69))
		return (write(2, "minishell: syntax error !!\n", 28), 0);
	return (1);
}

t_lexer_list	*lexer(t_shell *shell)
{
	if (!shell->rl_copy)
		return (NULL);
	shell->lex_head = tokenize(shell);
	if (!shell->lex_head)
		return (NULL);
	return (shell->lex_head);
}

int	check_syntax(char *input)
{
	int	j;

	j = 0;
	if (!check_quote_syntax(input))
	{
		ft_putstr_fd("minishell:  syntax error !!\n", 2);
		exit_status(EXIT_SET, 2);
		return (0);
	}
	if (!check_redirect_in(input, j) || \
		!check_redirect_out(input, j))
	{
		exit_status(EXIT_SET, 2);
		return (0);
	}
	if (check_pipe(input) == 0)
	{
		ft_putstr_fd("minishell:  syntax error near unexpected token `|'\n", 2);
		exit_status(EXIT_SET, 2);
		return (0);
	}
	return (1);
}

bool	parser(t_shell *shell)
{
	shell->lex_head = lexer(shell);
	if (!shell->lex_head)
		return (false);
	shell->executor = prepare_executor(shell);
	return (true);
}
