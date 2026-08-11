/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map4_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:52:52 by asebban           #+#    #+#             */
/*   Updated: 2025/02/17 15:16:20 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	int	check_map_char(char c, t_game *game, int i, int j)
{
	if (i >= game->map->height || j >= game->map->width)
		return (0);
	if (c == 'P')
	{
		game->player_count++;
		game->player_x = j;
		game->player_y = i;
	}
	else if (c == 'E')
		game->exit_count++;
	else if (c == 'C')
		game->total_collectibles++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

int	validate_map_chars(t_game *game)
{
	int	i;
	int	j;

	game->player_count = 0;
	game->exit_count = 0;
	game->total_collectibles = 0;
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (!check_map_char(game->map->matrice[i][j], game, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (game->player_count == 1 && game->exit_count == 1
		&& game->total_collectibles > 0);
}
