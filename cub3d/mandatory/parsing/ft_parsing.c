/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:20 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:20 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_parsing *p)
{
	if (p->no_texture)
		free(p->no_texture);
	if (p->so_texture)
		free(p->so_texture);
	if (p->we_texture)
		free(p->we_texture);
	if (p->ea_texture)
		free(p->ea_texture);
}

static bool	has_cub_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

bool	ft_parsing(const char *filename, t_parsing *parsing)
{
	int			fd;
	t_parsing	tmp;
	char		*first_line;

	if (!has_cub_extension(filename))
		return (ft_print_error("Error\nFile must have a \
.cub extension\n"), false);
	first_line = NULL;
	ft_initialisation(&tmp);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_print_error("Error\nCannot open .cub file\n"), false);
	if (!ft_parse_header(fd, &tmp, &first_line))
		return (free_textures(&tmp), close(fd), false);
	if (!ft_parse_map(fd, first_line, &tmp))
		return (free_textures(&tmp), close(fd), false);
	close(fd);
	*parsing = tmp;
	return (true);
}
