/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:39:09 by hfalati           #+#    #+#             */
/*   Updated: 2025/06/24 11:39:09 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			delta_x;

	(void)y;
	if (last_x == -1)
		last_x = x;
	delta_x = x - last_x;
	rotate_player(game, delta_x * 0.003);
	last_x = x;
	return (0);
}

int	main(int ac, char **argv)
{
	t_parsing	p;
	t_game		g;

	if (ac != 2)
	{
		ft_print_error("Error\nUsage: ./cub3D <map.cub>\n");
		return (EXIT_FAILURE);
	}
	if (!ft_parsing(argv[1], &p))
		exit(1);
	g.parsing = &p;
	if (!ft_init_game(&g, &p))
	{
		ft_print_error("Error\nGame initialization failed\n");
		return (cleanup_game(&g), EXIT_FAILURE);
	}
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.win, 17, 1L << 17, close_game, &g);
	mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
	mlx_loop_hook(g.mlx, ft_game_loop, &g);
	mlx_loop(g.mlx);
	cleanup_game(&g);
	return (0);
}
