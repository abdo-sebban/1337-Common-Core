/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:56 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:56 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	gather_map_lines(int fd, char *first_map_line,
	char ***out_raw_map_lines, int *out_map_line_count)
{
	if (!ft_collect(fd, first_map_line,
			out_raw_map_lines, out_map_line_count))
	{
		ft_print_error("Error\nFailed to collect map lines.\n");
		return (false);
	}
	return (true);
}

static int	compute_max_width(char **raw_map_lines, int map_line_count)
{
	int	max_width;
	int	i;
	int	len;

	max_width = 0;
	i = 0;
	len = 0;
	while (i < map_line_count)
	{
		len = ft_strlen(raw_map_lines[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

static void	free_matrix(char **raw_map_lines, int map_line_count)
{
	int	i;

	i = 0;
	if (!raw_map_lines)
		return ;
	while (i < map_line_count)
	{
		free(raw_map_lines[i]);
		i++;
	}
	free(raw_map_lines);
}

bool	ft_parse_map(int fd, char *first_map_line, t_parsing *p)
{
	char	**matrix;
	int		map_line_count;
	int		max_width;

	matrix = NULL;
	map_line_count = 0;
	if (!gather_map_lines(fd, first_map_line, &matrix, &map_line_count))
		return (false);
	max_width = compute_max_width(matrix, map_line_count);
	if (!is_valide_map(matrix, map_line_count, max_width, p))
	{
		free_matrix(matrix, map_line_count);
		return (false);
	}
	if (!allocate_map_matrix(matrix, map_line_count, max_width, p))
	{
		free_matrix(matrix, map_line_count);
		return (false);
	}
	free_matrix(matrix, map_line_count);
	return (true);
}
