/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:32:51 by asebban           #+#    #+#             */
/*   Updated: 2025/02/24 10:58:36 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->map->width * 32,
			game->map->height * 32, "so_long");
	if (!game->win)
	{
		free(game->mlx);
		game->mlx = NULL;
		return (0);
	}
	game->moves = 0;
	game->collectibles = 0;
	return (1);
}

static	void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	if (map->matrice)
	{
		while (i < map->height)
		{
			if (map->matrice[i])
				free(map->matrice[i]);
			i++;
		}
		free(map->matrice);
	}
	free(map);
}

void	clean_game(t_game *game)
{
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	if (game->map)
		free_map(game->map);
}

static	int	load_image(t_game	*game)
{
	int	widht;
	int	height;

	widht = TILE_SIZE;
	height = TILE_SIZE;
	game->imgs.wall = mlx_xpm_file_to_image(game->mlx,
			"utils/../textures/walls/11zon_so-long-wall.xpm", &widht, &height);
	game->imgs.player = mlx_xpm_file_to_image(game->mlx,
			"utils/../textures/player/11zon_icons8-pixel-cat-40.xpm", &widht,
			&height);
	game->imgs.collectible = mlx_xpm_file_to_image(game->mlx,
			"utils/../textures/coins/11zon_icons8-undertale-heart-30.xpm",
			&widht, &height);
	game->imgs.exit = mlx_xpm_file_to_image(game->mlx,
			"utils/../textures/exit/house.xpm", &widht, &height);
	game->imgs.floor = mlx_xpm_file_to_image(game->mlx,
			"utils/../textures/floor/base.xpm", &widht, &height);
	if (!game->imgs.wall || !game->imgs.player || !game->imgs.collectible
		|| !game->imgs.exit || !game->imgs.floor)
	{
		image_free(game);
		return (0);
	}
	return (1);
}

int	setup_game(t_game *game, char *file)
{
	if (!parse_map(game, file))
	{
		ft_printf("Error\nInvalid map!\n");
		return (0);
	}
	if (!init_game(game))
	{
		clean_game(game);
		return (0);
	}
	if (!load_image(game))
	{
		clean_game(game);
		ft_printf("can't load images");
		return (0);
	}
	return (1);
}
