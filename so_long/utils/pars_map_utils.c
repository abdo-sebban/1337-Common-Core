/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:34:11 by asebban           #+#    #+#             */
/*   Updated: 2025/02/24 10:55:34 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	int	validate_line_length(char *line, int width)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	return (len == width);
}

static	int	get_map_dimensions(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map->height = 0;
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), 0);
	game->map->width = ft_strlen(line) -1 ;
	while (line)
	{
		if (!validate_line_length(line, game->map->width))
		{
			free(line);
			close(fd);
			return (0);
		}
		game->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (game->map->height > 0 && game->map->width > 0);
}

static	int	open_map_file(char *filename, t_game *game, int height)
{
	int	fd;

	game->map->matrice = malloc(sizeof(char *) * height);
	if (!game->map->matrice)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map->matrice);
		return (-1);
	}
	return (fd);
}

static	int	allocate_and_fill_map(char *filename, t_game *game)
{
	int	fd;

	fd = open_map_file(filename, game, game->map->height);
	if (fd < 0 || !game->map->matrice)
		return (0);
	if (!fill_map_matrice(fd, game))
		return (0);
	close(fd);
	return (1);
}

int	parse_map(t_game *game, char *filename)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (0);
	if (!get_map_dimensions(filename, game)
		|| game->map->height > 37 || game->map->width > 76)
	{
		free(game->map);
		return (0);
	}
	if (!allocate_and_fill_map(filename, game))
	{
		free(game->map);
		return (0);
	}
	if (!validate_walls(game) || !validate_map_chars(game)
		|| !validate_map_playability(game))
	{
		free_matrice(game->map->matrice, game->map->height);
		free(game->map);
		return (0);
	}
	return (1);
}
