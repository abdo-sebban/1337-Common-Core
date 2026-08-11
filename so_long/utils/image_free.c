/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:29:11 by asebban           #+#    #+#             */
/*   Updated: 2025/02/21 10:27:30 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	image_free(t_game *game)
{
	if (game->imgs.wall)
		mlx_destroy_image(game->mlx, game->imgs.wall);
	if (game->imgs.player)
		mlx_destroy_image(game->mlx, game->imgs.player);
	if (game->imgs.collectible)
		mlx_destroy_image(game->mlx, game->imgs.collectible);
	if (game->imgs.exit)
		mlx_destroy_image(game->mlx, game->imgs.exit);
	if (game->imgs.floor)
		mlx_destroy_image(game->mlx, game->imgs.floor);
}
