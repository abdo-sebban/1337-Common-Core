/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:41 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:41 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static bool	assign_texture(char **dest, const char *path)
{
	char	*trimmed;
	int		fd;

	if (*dest != NULL)
		return (ft_print_error("Error\nDuplicate texture path\n"), false);
	trimmed = ft_strtrim(path, " \t\n");
	if (!trimmed)
		return (ft_print_error("Error\nft_strtrim failed\n"), false);
	if (!file_has_xpm_extension(trimmed))
	{
		(ft_print_error("Error\nTexture missing \".xpm\"\n"), free(trimmed));
		return (false);
	}
	fd = open(trimmed, O_RDONLY);
	if (fd < 0)
		return (free(trimmed), \
ft_print_error("Error\nCannot open texture file\n"), false);
	close(fd);
	*dest = ft_strdup(trimmed);
	free(trimmed);
	if (!*dest)
		return (ft_print_error("Error\nft_strdup failed"), false);
	return (true);
}

static bool	parse_texture_line(char *line, char **id, char **path)
{
	if (!line || !id || !path)
		return (false);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	*id = line;
	while (*line && *line != ' ' && *line != '\t')
		line++;
	if (*line)
		*line++ = '\0';
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line == '\0')
		return (ft_print_error("Error\nMissing texture path\n"), false);
	*path = line;
	return (true);
}

bool	set_texture_path(char *line, t_parsing *p)
{
	char	*id;
	char	*path;

	if (!parse_texture_line(line, &id, &path))
		return (false);
	if (ft_strcmp(id, "NO") == 0)
		return (assign_texture(&p->no_texture, path));
	else if (ft_strcmp(id, "SO") == 0)
		return (assign_texture(&p->so_texture, path));
	else if (ft_strcmp(id, "WE") == 0)
		return (assign_texture(&p->we_texture, path));
	else if (ft_strcmp(id, "EA") == 0)
		return (assign_texture(&p->ea_texture, path));
	ft_print_error("Error\nUnknown texture identifier\n");
	return (false);
}
