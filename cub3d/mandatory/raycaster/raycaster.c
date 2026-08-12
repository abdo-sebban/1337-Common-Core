/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:27:16 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/13 20:22:50 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calc_tex_x(t_game *game)
{
	double	hit_pos;
	int		texture_x;

	if (game->ray.side == 0)
		hit_pos = game->player.pos.y + game->ray.perp_wall_dist \
			* game->ray.dir.y;
	else
		hit_pos = game->player.pos.x + game->ray.perp_wall_dist \
			* game->ray.dir.x;
	hit_pos = hit_pos - (int)hit_pos;
	texture_x = (int)(hit_pos * TEX_SIZE);
	return (texture_x);
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	int	*buffer;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	buffer = (int *)texture->data;
	return (buffer[y * texture->width + x]);
}

void	draw_stripe(t_game *game, int x, int tex, int tex_x)
{
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	step = 1.0 * TEX_SIZE / game->line_height;
	tex_pos = (game->draw_start - game->screen_height / 2 \
		+ game->line_height / 2) * step;
	while (game->draw_start < game->draw_end)
	{
		tex_y = (int)tex_pos % TEX_SIZE;
		tex_pos += step;
		color = get_texture_pixel(&game->textures[tex], tex_x, tex_y);
		my_mlx_pixel_put(&game->screen, x, game->draw_start, color);
		game->draw_start++;
	}
}

void	cast_single_ray(t_game *game, int x)
{
	int		tex_num;
	int		tex_x;

	game->draw_start = 0;
	game->draw_end = 0;
	game->line_height = 0;
	init_ray_dir(game, x);
	init_delta_dist(game);
	init_first_step(game);
	perform_dda(game);
	calc_player_to_wall(game);
	calc_wall_line(game);
	tex_num = select_texture(game);
	tex_x = calc_tex_x(game);
	draw_stripe(game, x, tex_num, tex_x);
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->screen_width)
	{
		cast_single_ray(game, x);
		x++;
	}
}
