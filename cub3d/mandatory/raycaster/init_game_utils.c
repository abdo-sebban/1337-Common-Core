/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:00:44 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/13 15:24:14 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player_east_west(t_game *game, char player_dir)
{
	if (player_dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
	else if (player_dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
}

int	init_player(t_game *game, t_parsing *parsing)
{
	game->player.pos.x = parsing->player_pos.x;
	game->player.pos.y = parsing->player_pos.y;
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
	if (parsing->player_dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	else if (parsing->player_dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	else
	{
		init_player_east_west(game, parsing->player_dir);
	}
	return (1);
}
