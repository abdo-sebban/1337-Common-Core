/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:00:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/08 03:35:59 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	game->running = 0;
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

void	cleanup_parsing(t_game *game)
{
	if (game->parsing->we_texture)
		free(game->parsing->we_texture);
	if (game->parsing->no_texture)
		free(game->parsing->no_texture);
	if (game->parsing->so_texture)
		free(game->parsing->so_texture);
	if (game->parsing->ea_texture)
		free(game->parsing->ea_texture);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
	{
		i = -1;
		while (game->map[++i])
			free(game->map[i]);
		free(game->map);
	}
	cleanup_parsing(game);
}
