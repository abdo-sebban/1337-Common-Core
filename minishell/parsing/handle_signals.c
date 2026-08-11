/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:34:48 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/08 22:44:49 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signals;

void	parent_handler(int signum)
{
	(void)signum;
	if (g_signals == 0)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status(EXIT_SET, 130);
	}
}

void	heredoc_handler(int signum)
{
	(void) signum;
	if (g_signals == 69)
	{
		g_signals = 130;
		close(0);
		write(2, "\n", 1);
	}
}

void	signal_setup(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, parent_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
