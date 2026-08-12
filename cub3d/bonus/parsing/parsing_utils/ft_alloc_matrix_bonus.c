/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:21 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:21 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_matrix(char **map, int filled_rows)
{
	while (--filled_rows >= 0)
		free(map[filled_rows]);
	free(map);
}

static bool	allocate_single_map_row(char **raw_map_lines,
										int row, int max_width, t_parsing *p)
{
	int	row_len;
	int	c;

	row_len = ft_strlen(raw_map_lines[row]);
	p->map[row] = malloc(sizeof(char) * (max_width + 1));
	if (!p->map[row])
	{
		ft_print_error("Error\nFailed to allocate map row.\n");
		return (false);
	}
	ft_memcpy(p->map[row], raw_map_lines[row], row_len);
	c = row_len;
	while (c < max_width)
		1 && (p->map[row][c] = ' ', c++);
	1 && (p->map[row][max_width] = '\0');
	return (true);
}

bool	allocate_map_matrix(char **raw_map_lines,
		int map_line_count, int max_width, t_parsing *p)
{
	int	r;

	1 && (r = 0, p->map = malloc(sizeof(char *) * (map_line_count + 1)));
	if (!p->map)
	{
		ft_print_error("Error\nFailed to allocate map row pointers.\n");
		return (false);
	}
	while (r < map_line_count)
	{
		if (!allocate_single_map_row(raw_map_lines, r, max_width, p))
		{
			free_matrix(p->map, r);
			p->map = NULL;
			return (false);
		}
		r++;
	}
	p->map[map_line_count] = NULL;
	1 && (p->map_width = max_width, p->map_height = map_line_count);
	return (true);
}
