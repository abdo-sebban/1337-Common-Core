/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:02:03 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/08 04:25:39 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_texture_paths(char *texture_paths[7], t_parsing *parsing)
{
	texture_paths[NORTH_TEX] = parsing->no_texture;
	texture_paths[SOUTH_TEX] = parsing->so_texture;
	texture_paths[WEST_TEX] = parsing->we_texture;
	texture_paths[EAST_TEX] = parsing->ea_texture;
	texture_paths[4] = "bonus/textures/door.xpm";
	texture_paths[5] = "bonus/textures/weapon_holding.xpm";
	texture_paths[6] = "bonus/textures/weapon_shooting_0.xpm";
	texture_paths[7] = "bonus/textures/weapon_shooting_1.xpm";
	texture_paths[8] = "bonus/textures/weapon_shooting_2.xpm";
	texture_paths[9] = "bonus/textures/weapon_shooting_3.xpm";
	texture_paths[10] = "bonus/textures/weapon_shooting_4.xpm";
	texture_paths[11] = "bonus/textures/weapon_shooting_5.xpm";
	texture_paths[12] = "bonus/textures/weapon_shooting_6.xpm";
	texture_paths[13] = "bonus/textures/weapon_shooting_7.xpm";
	texture_paths[14] = "bonus/textures/weapon_shooting_8.xpm";
}

int	init_textures(t_game *game, t_parsing *parsing)
{
	char	*texture_paths[15];
	int		i;

	init_texture_paths(texture_paths, parsing);
	i = 0;
	while (i < 15)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, \
													texture_paths[i], \
													&game->textures[i].width, \
													&game->textures[i].height);
		if (!game->textures[i].img)
			return (0);
		game->textures[i].data = mlx_get_data_addr(game->textures[i].img, \
												&game->textures[i].bpp, \
												&game->textures[i].line_len, \
												&game->textures[i].endian);
		i++;
	}
	return (1);
}

void	init_game_data(t_game *game, t_parsing *parsing)
{
	int	i;

	game->screen.width = game->screen_width;
	game->screen.height = game->screen_height;
	game->map = parsing->map;
	game->map_height = parsing->map_height;
	game->map_width = parsing->map_width;
	game->floor_color = parsing->floor_color;
	game->ceiling_color = parsing->ceiling_color;
	game->door_status = 0;
	i = 0;
	while (i < 15)
	{
		game->textures[i].img = NULL;
		i++;
	}
	game->screen.img = NULL;
	game->win = NULL;
}

int	init_door_status(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->door_status = malloc(sizeof(int *) * game->map_height);
	if (!game->door_status)
		return (0);
	while (i < game->map_height)
	{
		game->door_status[i] = malloc(sizeof(int) * game->map_width);
		if (!game->door_status[i])
		{
			free_door_status(game, i);
			return (0);
		}
		j = 0;
		while (j < game->map_width)
		{
			game->door_status[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_init_game(t_game *game, t_parsing *parsing)
{
	game->screen_width = SCREEN_WIDTH;
	game->screen_height = SCREEN_HEIGHT;
	init_game_data(game, parsing);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->screen_width, \
									game->screen_height, "Cub3D");
	if (!game->win)
		return (0);
	game->screen.img = mlx_new_image(game->mlx, game->screen_width, \
									game->screen_height);
	if (!game->screen.img)
		return (0);
	game->screen.data = mlx_get_data_addr(game->screen.img, &game->screen.bpp, \
								&game->screen.line_len, &game->screen.endian);
	if (!init_player(game, parsing))
		return (0);
	if (!init_textures(game, parsing))
		return (0);
	if (!init_door_status(game))
		return (0);
	init_keys(&game->keys, game);
	return (1);
}
