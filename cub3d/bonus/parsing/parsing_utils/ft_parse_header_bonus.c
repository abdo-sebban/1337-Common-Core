/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:00 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:00 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_readline(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line_is_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static bool	handle_color_line(char *line, t_parsing *p, int *header_count)
{
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (!set_floor_color(line, p))
			return (false);
	}
	else
	{
		if (!set_ceiling_color(line, p))
			return (false);
	}
	(*header_count)++;
	return (true);
}

static bool	handle_texture_line(char *line, t_parsing *p, int *header_count)
{
	if (!set_texture_path(line, p))
		return (false);
	(*header_count)++;
	return (true);
}

bool	ft_check_header_line(char *line, t_parsing *p,
								int *header_count, char **first_map_line)
{
	char	*trimmed;

	trimmed = line;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (is_texture_line(trimmed))
		return (handle_texture_line(trimmed, p, header_count));
	else if (trimmed[0] == 'F' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (handle_color_line(trimmed, p, header_count));
	else if (trimmed[0] == 'C' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (handle_color_line(trimmed, p, header_count));
	else
	{
		*first_map_line = ft_strdup(line);
		if (!*first_map_line)
		{
			ft_print_error("Error\nft_strdup failed\n");
			return (false);
		}
		return (true);
	}
}

bool	ft_parse_header(int fd, t_parsing *parsing, char **first_line)
{
	char	*line;
	int		count;

	count = 0;
	*first_line = NULL;
	line = ft_readline(fd);
	while (count <= 6 && line)
	{
		if (!ft_check_header_line(line, parsing, &count, first_line))
			return (free(line), false);
		if (*first_line)
		{
			free(line);
			break ;
		}
		free(line);
		line = ft_readline(fd);
	}
	if (count < 6)
		return (ft_print_error("Error\nNot all textures/colors provided.\n"), \
false);
	if (!*first_line)
		return (ft_print_error("Error\nUnexpected EOF before map.\n"),
			free(line), false);
	return (true);
}
