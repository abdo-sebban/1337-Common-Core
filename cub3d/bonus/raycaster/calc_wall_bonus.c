/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:09:45 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/27 21:26:38 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_player_to_wall(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos.x \
			+ (1 - game->ray.step_x) / 2) / game->ray.dir.x;
	else
		game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos.y \
			+ (1 - game->ray.step_y) / 2) / game->ray.dir.y;
}

void	calc_wall_line(t_game *game)
{
	game->line_height = (int)(game->screen_height / game->ray.perp_wall_dist);
	game->draw_start = -(game->line_height) / 2 + game->screen_height / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + game->screen_height / 2;
	if (game->draw_end >= game->screen_height)
		game->draw_end = game->screen_height - 1;
}

int	select_texture(t_game *game)
{
	if (game->ray.hit == 2)
		return (4);
	if (game->ray.side == 0)
	{
		if (game->ray.dir.x > 0)
			return (WEST_TEX);
		return (EAST_TEX);
	}
	if (game->ray.dir.y > 0)
		return (NORTH_TEX);
	return (SOUTH_TEX);
}
