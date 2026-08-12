/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:42:00 by hfalati           #+#    #+#             */
/*   Updated: 2025/08/08 05:11:23 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
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
	else if (keycode == KEY_F)
		handle_door_interaction(game);
	if (keycode == 14)
		game->keys.shot = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
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

void	calculate_corners(t_vector new_pos, int corners[4][2])
{
	corners[0][0] = (int)(new_pos.y + 0.05);
	corners[0][1] = (int)(new_pos.x + 0.05);
	corners[1][0] = (int)(new_pos.y + 0.05);
	corners[1][1] = (int)(new_pos.x - 0.05);
	corners[2][0] = (int)(new_pos.y - 0.05);
	corners[2][1] = (int)(new_pos.x + 0.05);
	corners[3][0] = (int)(new_pos.y - 0.05);
	corners[3][1] = (int)(new_pos.x - 0.05);
}
