/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:47:56 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 19:55:35 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signals;

static	char	*read_input(char *input)
{
	char	*line;

	(void)input;
	signal_setup(PARENT);
	g_signals = 0;
	line = readline("\001\033[0;32m\002minishell-1.0$~ \001\033[0m\002");
	g_signals = 1;
	return (line);
}

static	bool	handle_eof1(char *input, t_shell *shell)
{
	(void)shell;
	if (!input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		ft_malloc(0, 0);
		exit(exit_status(0, 0));
	}
	return (true);
}

static	char	*preprocess_input(char *raw, t_shell *shell)
{
	char	*processed;

	if (*raw)
		add_history(raw);
	if (!check_syntax(raw))
	{
		free(raw);
		return (NULL);
	}
	processed = clean_rl_copy(raw);
	free(raw);
	processed = process_line_expand_first_var(processed, shell);
	if (!processed)
		return (NULL);
	processed = handle_dollar_quotes(processed);
	if (!processed)
		return (NULL);
	processed = replace_var_equals_var(processed, shell);
	if (!processed)
		return (NULL);
	processed = export_hard(processed, shell);
	return (processed);
}

static	void	parse_and_execute(t_shell *shell)
{
	shell->rl_copy = replace_vars1(shell->rl_input, shell);
	replace_soh_with_dollar(shell->rl_copy);
	replace_soh_with_dollar_in_env(shell->env);
	if (!shell->rl_copy)
		return ;
	if (!parser(shell))
		return ;
	executor(shell);
}

void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (true)
	{
		if (!check_tty())
			return ;
		input = read_input(input);
		if (!handle_eof1(input, shell))
			continue ;
		shell->rl_input = preprocess_input(input, shell);
		if (!shell->rl_input)
			continue ;
		parse_and_execute(shell);
		close_all_fds();
	}
}
