/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:14:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/08 05:04:27 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(angle) \
		- game->player.dir.y * sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + \
		game->player.dir.y * cos(angle);
	game->player.plane.x = game->player.plane.x * \
		cos(angle) - game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) \
		+ game->player.plane.y * cos(angle);
}

int	is_collision(t_game *game, t_vector new_pos)
{
	int	corners[4][2];
	int	i;
	int	x;
	int	y;

	calculate_corners(new_pos, corners);
	i = 0;
	while (i < 4)
	{
		y = corners[i][0];
		x = corners[i][1];
		if (y >= 0 && y < game->map_height
			&& x >= 0 && x < game->map_width)
		{
			if (game->map[y][x] == '1')
				return (1);
			if (game->map[y][x] == 'D' && game->door_status[y][x] == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void	handle_movement_a_d(t_game *game)
{
	t_vector	new_pos;

	if (game->keys.a)
	{
		new_pos.x = game->player.pos.x - game->player.plane.x \
			* game->player.move_speed;
		new_pos.y = game->player.pos.y - game->player.plane.y \
			* game->player.move_speed;
		if (is_collision(game, new_pos))
			return ;
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
	if (game->keys.d)
	{
		new_pos.x = game->player.pos.x + game->player.plane.x \
			* game->player.move_speed;
		new_pos.y = game->player.pos.y + game->player.plane.y \
			* game->player.move_speed;
		if (is_collision(game, new_pos))
			return ;
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
}

void	handle_movement_w_s(t_game *game)
{
	t_vector	new_pos;

	if (game->keys.w)
	{
		new_pos.x = game->player.pos.x + game->player.dir.x \
			* game->player.move_speed;
		new_pos.y = game->player.pos.y + game->player.dir.y \
			* game->player.move_speed;
		if (is_collision(game, new_pos))
			return ;
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
	if (game->keys.s)
	{
		new_pos.x = game->player.pos.x - game->player.dir.x \
			* game->player.move_speed;
		new_pos.y = game->player.pos.y - game->player.dir.y \
			* game->player.move_speed;
		if (is_collision(game, new_pos))
			return ;
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
}

void	update_player(t_game *game)
{
	handle_movement_w_s(game);
	handle_movement_a_d(game);
	if (game->keys.right)
		rotate_player(game, game->player.rot_speed);
	if (game->keys.left)
		rotate_player(game, -game->player.rot_speed);
}
