/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map3_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:51:08 by asebban           #+#    #+#             */
/*   Updated: 2025/02/20 16:34:32 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	int	check_horizontal_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->width)
	{
		if (game->map->matrice[0][i] != '1' ||
		game->map->matrice[game->map->height - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static	int	check_vertical_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->height)
	{
		if (game->map->matrice[i][0] != '1' ||
			game->map->matrice[i][game->map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	validate_walls(t_game *game)
{
	return (check_horizontal_walls(game) && check_vertical_walls(game));
}
