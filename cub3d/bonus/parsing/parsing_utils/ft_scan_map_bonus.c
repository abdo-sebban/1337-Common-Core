/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:28 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:28 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_valid_map_char(char ch)
{
	if (ch == '0' || ch == '1' || ch == ' '
		|| ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W' || ch == 'D')
		return (true);
	ft_print_error("Error\nInvalid character\n");
	return (false);
}

static bool	process_player_char(char ch, int r, int c, t_scan *scan)
{
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
	{
		if (*scan->player_found)
		{
			ft_print_error("Error\nMultiple player starting positions found\n");
			return (false);
		}
		*scan->player_found = true;
		scan->p->player_dir = ch;
		scan->p->player_pos.x = c + 0.5;
		scan->p->player_pos.y = r + 0.5;
	}
	return (true);
}

static bool	check_map_enclosure(char ch, int r, int c, t_scan *scan)
{
	if ((r == 0 || r == scan->height - 1 || c == 0 || c == scan->width - 1)
		&& (ch == '0' || ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W'
			|| ch == 'D'))
	{
		ft_print_error("Error\nMap not closed by walls\n");
		return (false);
	}
	return (true);
}

static bool	scan_row(int r, t_scan *scan)
{
	int		c;
	int		len;
	char	ch;

	c = 0;
	len = ft_strlen(scan->map_lines[r]);
	while (c < scan->width)
	{
		if (c < len)
			ch = scan->map_lines[r][c];
		else
			ch = ' ';
		if (!is_valid_map_char(ch))
			return (false);
		if (!process_player_char(ch, r, c, scan))
			return (false);
		if (!check_map_enclosure(ch, r, c, scan))
			return (false);
		++c;
	}
	return (true);
}

bool	scan_and_locate_player(char **map_lines,
		int height, int width, t_parsing *p)
{
	bool	player_found;
	t_scan	scan;
	int		r;

	player_found = false;
	scan.map_lines = map_lines;
	scan.height = height;
	scan.width = width;
	scan.p = p;
	scan.player_found = &player_found;
	r = 0;
	while (r < height)
	{
		if (!scan_row(r, &scan))
			return (false);
		++r;
	}
	if (!player_found)
	{
		ft_print_error("Error\nNo player starting position found in map\n");
		return (false);
	}
	return (true);
}
