/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:02:57 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/07 09:52:18 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_first_step(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist.x = (game->player.pos.x
				- game->ray.map_x) * game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist.x = (game->ray.map_x + 1.0
				- game->player.pos.x) * game->ray.delta_dist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist.y = (game->player.pos.y
				- game->ray.map_y) * game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist.y = (game->ray.map_y + 1.0
				- game->player.pos.y) * game->ray.delta_dist.y;
	}
}

void	init_delta_dist(t_game *game)
{
	if (game->ray.dir.x == 0)
		game->ray.delta_dist.x = 1e30;
	else
		game->ray.delta_dist.x = fabs(1 / game->ray.dir.x);
	if (game->ray.dir.y == 0)
		game->ray.delta_dist.y = 1e30;
	else
		game->ray.delta_dist.y = fabs(1 / game->ray.dir.y);
}

void	init_ray_dir(t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->screen_width - 1;
	game->ray.dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	game->ray.dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	game->ray.map_x = (int)game->player.pos.x;
	game->ray.map_y = (int)game->player.pos.y;
}
