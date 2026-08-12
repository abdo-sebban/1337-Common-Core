/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:55:19 by asebban           #+#    #+#             */
/*   Updated: 2025/07/30 13:36:40 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_trim_map(char **map_lines, int height)
{
	char	*trimmed_line;
	int		i;

	i = 0;
	while (i < height)
	{
		trimmed_line = ft_strtrim(map_lines[i], "\n");
		if (!trimmed_line)
			return (false);
		free(map_lines[i]);
		map_lines[i] = trimmed_line;
		i++;
	}
	return (true);
}

static bool	check_basic_args(char **map_lines,
				int height, int width, t_parsing *p)
{
	if (!map_lines || height <= 0 || width <= 0 || !p)
		return (false);
	return (true);
}

static bool	find_max_width_and_check_lengths(char **map_lines,
			int height, int width)
{
	int	r;
	int	len;

	r = 0;
	while (r < height)
	{
		len = ft_strlen(map_lines[r]);
		if (len > width)
		{
			ft_print_error("Error\nMap line length exceeds width \n");
			return (false);
		}
		r++;
	}
	return (true);
}

bool	check_doors_between_walls(char **map_lines, int height, int width)
{
	int		y;
	int		x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map_lines[y][x] == 'D')
			{
				if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
				{
					if (!is_door_valid(map_lines, x, y))
						return (false);
				}
				else
					return (ft_print_error("Error\nDoor is not between \
two walls!\n"), false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	is_valide_map(char **map_lines, int height, int width, t_parsing *p)
{
	if (!ft_trim_map(map_lines, height))
		return (false);
	if (!check_basic_args(map_lines, height, width, p))
		return (false);
	if (!find_max_width_and_check_lengths(map_lines, height, width))
		return (false);
	if (!scan_and_locate_player(map_lines, height, width, p))
		return (false);
	if (!check_interior_leaks(map_lines, height, width))
		return (false);
	if (!check_doors_between_walls(map_lines, height, width))
		return (false);
	p->map_width = width;
	p->map_height = height;
	return (true);
}
