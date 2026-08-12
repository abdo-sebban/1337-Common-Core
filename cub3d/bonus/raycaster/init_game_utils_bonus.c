/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:33:40 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/04 00:51:27 by hfalati          ###   ########.fr       */
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

void	init_keys(t_keys *keys, t_game *game)
{
	keys->shot = 0;
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
	keys->f = 0;
	game->running = 1;
	game->frame_time = 0;
	game->old_time = 0;
}
