/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:04:45 by asebban           #+#    #+#             */
/*   Updated: 2025/08/08 08:15:08 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square(t_image *img, int pos[2], int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, pos[0] + j, pos[1] + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	pos[2];
	int	offset;

	offset = (MINI_TILE_SIZE - PLAYER_SQUARE_SIZE) / 2;
	pos[0] = MINI_MAP_OFFSET_X
		+ (int)(game->player.pos.x * MINI_TILE_SIZE) + offset;
	pos[1] = MINI_MAP_OFFSET_Y
		+ (int)(game->player.pos.y * MINI_TILE_SIZE) + offset;
	draw_square(&game->screen, pos, PLAYER_SQUARE_SIZE, 16711680);
}

static void	get_tile_coordinates(t_game *game, int xy[2], int coords[2])
{
	int	player_tile_x;
	int	player_tile_y;
	int	window_start_x;
	int	window_start_y;

	player_tile_x = (int)game->player.pos.x;
	player_tile_y = (int)game->player.pos.y;
	window_start_y = player_tile_y - MINI_MAP_WINDOW_HEIGHT / 2;
	window_start_x = player_tile_x - MINI_MAP_WINDOW_WIDTH / 2;
	coords[0] = window_start_x + xy[0];
	coords[1] = window_start_y + xy[1];
}

static void	draw_minimap_tile(t_game *game, int xy[2])
{
	int	coords[2];
	int	screen_pos[2];

	get_tile_coordinates(game, xy, coords);
	if (coords[0] >= 0 && coords[0] < game->map_width
		&& coords[1] >= 0 && coords[1] < game->map_height)
	{
		screen_pos[0] = MINI_MAP_OFFSET_X + xy[0] * MINI_TILE_SIZE;
		screen_pos[1] = MINI_MAP_OFFSET_Y + xy[1] * MINI_TILE_SIZE;
		if (game->map[coords[1]][coords[0]] == '1')
			draw_square(&game->screen, screen_pos, MINI_TILE_SIZE, 16777215);
		else if (game->map[coords[1]][coords[0]] == 'D')
			draw_square(&game->screen, screen_pos, MINI_TILE_SIZE, 65280);
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	player_pos[2];
	int	tile_xy[2];
	int	offset;

	y = 0;
	while (y < MINI_MAP_WINDOW_HEIGHT)
	{
		x = 0;
		while (x < MINI_MAP_WINDOW_WIDTH)
		{
			tile_xy[0] = x;
			tile_xy[1] = y;
			draw_minimap_tile(game, tile_xy);
			x++;
		}
		y++;
	}
	offset = (MINI_TILE_SIZE - PLAYER_SQUARE_SIZE) / 2;
	player_pos[0] = MINI_MAP_OFFSET_X
		+ (MINI_MAP_WINDOW_WIDTH / 2) * MINI_TILE_SIZE + offset;
	player_pos[1] = MINI_MAP_OFFSET_Y
		+ (MINI_MAP_WINDOW_HEIGHT / 2) * MINI_TILE_SIZE + offset;
	draw_square(&game->screen, player_pos, PLAYER_SQUARE_SIZE, 16711680);
}
