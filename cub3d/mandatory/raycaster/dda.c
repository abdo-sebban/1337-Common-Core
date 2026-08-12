/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 06:18:15 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/07 10:02:22 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	return (game->map[y][x] == '1');
}

void	dda_step(t_game *game, int *side)
{
	if (game->ray.side_dist.x < game->ray.side_dist.y)
	{
		game->ray.side_dist.x += game->ray.delta_dist.x;
		game->ray.map_x += game->ray.step_x;
		*side = 0;
	}
	else
	{
		game->ray.side_dist.y += game->ray.delta_dist.y;
		game->ray.map_y += game->ray.step_y;
		*side = 1;
	}
}

void	perform_dda(t_game *game)
{
	int	flag;
	int	side;

	flag = 0;
	while (!flag)
	{
		dda_step(game, &side);
		if (is_wall(game, game->ray.map_x, game->ray.map_y))
			flag = 1;
	}
	game->ray.hit = flag;
	game->ray.side = side;
}
