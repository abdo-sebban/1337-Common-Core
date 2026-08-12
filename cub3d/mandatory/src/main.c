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
	mlx_loop_hook(g.mlx, ft_game_loop, &g);
	mlx_loop(g.mlx);
	cleanup_game(&g);
	return (0);
}
