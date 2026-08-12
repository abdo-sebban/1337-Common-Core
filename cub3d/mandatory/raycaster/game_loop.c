/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:02:19 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/01 08:07:02 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->data + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_background(t_game *game)
{
	int	x;
	int	y;
	int	half_heigh;

	half_heigh = game->screen_height / 2;
	y = -1;
	while (++y < half_heigh)
	{
		x = 0;
		while (x < game->screen_width)
		{
			my_mlx_pixel_put(&game->screen, x, y, game->ceiling_color);
			x++;
		}
	}
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			my_mlx_pixel_put(&game->screen, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

void	put_hands(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, \
		game->textures[4].img, 50, 20);
}

int	ft_game_loop(t_game *game)
{
	if (!game->running)
		exit(0);
	update_player(game);
	put_background(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	put_hands(game);
	return (0);
}
