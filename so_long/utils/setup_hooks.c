/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:47:05 by asebban           #+#    #+#             */
/*   Updated: 2025/02/22 10:32:57 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	int	handle_keypress(int keycode, t_game *game)
{
	int	moved;

	moved = 0;
	if (keycode == KEY_ESC)
	{
		clean_game(game);
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_UP)
		moved = move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		moved = move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		moved = move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		moved = move_player(game, 1, 0);
	if (moved)
	{
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
	}
	return (0);
}

static	int	handle_close(t_game *game)
{
	clean_game(game);
	exit(1);
	return (0);
}

static	void	render_tile(t_game *game, char tile, int x, int y)
{
	int	screen_x;
	int	screen_y;

	screen_x = x * TILE_SIZE;
	screen_y = y * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.floor,
		screen_x, screen_y);
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->imgs.wall,
			screen_x, screen_y);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->imgs.collectible,
			screen_x, screen_y);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->imgs.exit,
			screen_x, screen_y);
}

int	render_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			render_tile(game, game->map->matrice[y][x], x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.player,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 17, 1L << 17, handle_close, game);
	mlx_loop_hook(game->mlx, render_game, game);
}
