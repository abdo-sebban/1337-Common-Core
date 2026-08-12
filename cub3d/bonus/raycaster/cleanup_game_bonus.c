/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:00:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/08 07:50:59 by hfalati          ###   ########.fr       */
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

void	cleanup_parsing_and_doors(t_game *game)
{
	int	i;

	if (game->parsing->we_texture)
		free(game->parsing->we_texture);
	if (game->parsing->no_texture)
		free(game->parsing->no_texture);
	if (game->parsing->so_texture)
		free(game->parsing->so_texture);
	if (game->parsing->ea_texture)
		free(game->parsing->ea_texture);
	if (game->door_status)
	{
		i = 0;
		while (i < game->map_height)
		{
			free(game->door_status[i]);
			i++;
		}
		free(game->door_status);
	}
	exit(1);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 15)
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
	cleanup_parsing_and_doors(game);
}

void	free_door_status(t_game *game, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(game->door_status[i]);
		i++;
	}
	free(game->door_status);
	game->door_status = NULL;
}
