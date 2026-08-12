/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:10:17 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/08 06:24:50 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_door(t_game *game, int x, int y, float range)
{
	int		player_x;
	int		player_y;
	float	dist;

	player_x = (int)game->player.pos.x;
	player_y = (int)game->player.pos.y;
	if (x >= 0 && x < game->map_width
		&& y >= 0 && y < game->map_height
		&& game->map[y][x] == 'D')
	{
		dist = sqrt((x - player_x) * (x - player_x)
				+ (y - player_y) * (y - player_y));
		if (dist <= range)
			return (1);
	}
	return (0);
}

int	search_door_area(t_game *game, int player_x, int player_y,
					int door_coords[2])
{
	int		dy;
	int		dx;
	int		check_x;
	int		check_y;
	float	range;

	1 && (range = 1.5, dy = -3);
	while (++dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			1 && (check_x = player_x + dx, check_y = player_y + dy);
			if (check_x == player_x && check_y == player_y)
				;
			else if (is_valid_door(game, check_x, check_y, range))
			{
				door_coords[0] = check_x;
				door_coords[1] = check_y;
				return (1);
			}
			dx++;
		}
	}
	return (0);
}

int	find_nearest_door(t_game *game, int *door_x, int *door_y)
{
	int		player_x;
	int		player_y;
	int		door_coords[2];

	player_x = (int)game->player.pos.x;
	player_y = (int)game->player.pos.y;
	if (search_door_area(game, player_x, player_y, door_coords))
	{
		*door_x = door_coords[0];
		*door_y = door_coords[1];
		return (1);
	}
	return (0);
}

int	player_inside_door(t_game *game, int door_x, int door_y)
{
	return (game->player.pos.x >= door_x && \
			game->player.pos.x <= door_x + 1 && \
			game->player.pos.y >= door_y && \
			game->player.pos.y <= door_y + 1);
}

void	handle_door_interaction(t_game *game)
{
	int	door_x;
	int	door_y;

	if (find_nearest_door(game, &door_x, &door_y))
	{
		if (game->door_status[door_y][door_x] == 0)
			game->door_status[door_y][door_x] = 1;
		else if (game->door_status[door_y][door_x] == 1)
		{
			if (!player_inside_door(game, door_x, door_y))
				game->door_status[door_y][door_x] = 0;
		}
	}
}
