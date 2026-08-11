/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:07:46 by asebban           #+#    #+#             */
/*   Updated: 2025/02/24 11:58:06 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	int	is_valid_position(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height)
		return (0);
	if (game->map->matrice[y][x] == '1')
		return (0);
	return (1);
}

static	void	collect_item(t_game *game, int x, int y)
{
	game->collectibles++;
	game->map->matrice[y][x] = '0';
}

static	int	check_win_condition(t_game *game, int x, int y)
{
	if (game->map->matrice[y][x] != 'E')
		return (0);
	if (game->collectibles == game->total_collectibles)
	{
		ft_printf("You won in %d moves!\n", game->moves + 1);
		game->game_won = 1;
		return (1);
	}
	return (0);
}

int	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!is_valid_position(game, new_x, new_y))
		return (0);
	if (game->map->matrice[new_y][new_x] == 'C')
		collect_item(game, new_x, new_y);
	else if (check_win_condition(game, new_x, new_y) == 1)
	{
		clean_game(game);
		exit(0);
	}
	game->player_x = new_x;
	game->player_y = new_y;
	return (1);
}
