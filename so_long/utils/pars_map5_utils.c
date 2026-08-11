/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map5_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:55:26 by asebban           #+#    #+#             */
/*   Updated: 2025/02/17 15:16:20 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	void	flood_fill(char **matrice, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map->height || y >= game->map->width)
		return ;
	if (matrice[x][y] == '1' || matrice[x][y] == 'X')
		return ;
	if (matrice[x][y] == 'C')
		game->collectibles++;
	if (matrice[x][y] == 'E')
		game->game_won = 1;
	matrice[x][y] = 'X';
	flood_fill(matrice, x + 1, y, game);
	flood_fill(matrice, x - 1, y, game);
	flood_fill(matrice, x, y + 1, game);
	flood_fill(matrice, x, y - 1, game);
}

int	validate_map_playability(t_game *game)
{
	char	**temp_matrice;
	int		i;

	temp_matrice = malloc(sizeof(char *) * game->map->height);
	if (!temp_matrice)
		return (0);
	i = 0;
	while (i < game->map->height)
	{
		temp_matrice[i] = ft_strdup(game->map->matrice[i]);
		if (!temp_matrice[i])
		{
			free_matrice(temp_matrice, i);
			return (0);
		}
		i++;
	}
	game->collectibles = 0;
	game->game_won = 0;
	flood_fill(temp_matrice, game->player_y, game->player_x, game);
	free_matrice(temp_matrice, game->map->height);
	return (game->collectibles == game->total_collectibles && game->game_won);
}
