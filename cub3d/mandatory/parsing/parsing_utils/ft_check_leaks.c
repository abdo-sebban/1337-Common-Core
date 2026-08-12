/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_leaks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:54:42 by asebban           #+#    #+#             */
/*   Updated: 2025/07/30 08:22:47 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	get_char(char **map_lines, int row, int col, int height)
{
	int	len;

	if (row < 0 || row >= height)
		return (' ');
	len = ft_strlen(map_lines[row]);
	if (col < len)
		return (map_lines[row][col]);
	return (' ');
}

static bool	check_cell(char **map_lines, int r, int c, int height)
{
	char	left;
	char	right;
	char	up;
	char	down;
	char	ch;

	ch = get_char(map_lines, r, c, height);
	if (ch == '0' || ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
	{
		left = get_char(map_lines, r, c - 1, height);
		right = get_char(map_lines, r, c + 1, height);
		up = get_char(map_lines, r - 1, c, height);
		down = get_char(map_lines, r + 1, c, height);
		if (left == ' ' || right == ' ' || up == ' ' || down == ' ')
		{
			ft_print_error("Error\nMap leak detected\n");
			return (false);
		}
	}
	return (true);
}

bool	check_interior_leaks(char **map_lines, int height, int width)
{
	int	r;
	int	c;

	c = 1;
	r = 1;
	while (r < height - 1)
	{
		c = 1;
		while (c < width - 1)
		{
			if (!check_cell(map_lines, r, c, height))
				return (false);
			c++;
		}
		r++;
	}
	return (true);
}
