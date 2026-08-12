/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:06 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:06 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_print_error(const char *msg)
{
	if (!msg)
		return ;
	write(2, RED, ft_strlen(RED));
	write(2, msg, ft_strlen(msg));
	write(2, RESET, ft_strlen(RESET));
}

void	ft_initialisation(t_parsing *p)
{
	if (!p)
		return ;
	p->no_texture = NULL;
	p->so_texture = NULL;
	p->we_texture = NULL;
	p->ea_texture = NULL;
	p->floor_color = -1;
	p->ceiling_color = -1;
	p->map = NULL;
	p->map_width = 0;
	p->map_height = 0;
	p->player_pos.x = 0.0;
	p->player_pos.y = 0.0;
	p->player_dir = '\0';
}

bool	line_is_empty(const char *line)
{
	size_t	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		|| line[i] == '\r' || line[i] == '\f' || line[i] == '\v')
		i++;
	return (line[i] == '\0');
}

bool	is_texture_line(const char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if ((ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		&& (line[2] == ' ' || line[2] == '\t'))
		return (true);
	return (false);
}
