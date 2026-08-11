/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:15:51 by asebban           #+#    #+#             */
/*   Updated: 2025/02/24 11:11:22 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (handle_errors(ac, av[1]))
		exit(1);
	if (!setup_game(&game, av[1]))
		exit(1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	clean_game(&game);
	return (0);
}
