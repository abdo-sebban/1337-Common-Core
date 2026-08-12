/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:59:04 by hfalati           #+#    #+#             */
/*   Updated: 2025/07/13 15:10:47 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 14)
		game->keys.shot = 1;
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_ESC)
		close_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 14)
		game->keys.shot = 0;
	else if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}
