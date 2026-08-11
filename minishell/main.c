/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:02:28 by asebban           #+#    #+#             */
/*   Updated: 2025/04/16 14:02:28 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_signals;

static	void	ft_usage(void)
{
	printf("\033[0;31mUsage: ./minishell\033[0m\n");
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	shell = NULL;
	(void)av;
	if (ac != 1)
		return (ft_usage(), 1);
	g_signals = 1;
	rl_catch_signals = 0;
	shell = init_shell(env);
	if (!shell)
		return (1);
	minishell_loop(shell);
	ft_malloc(0, 0);
	return (0);
}
