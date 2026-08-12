/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:50 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:50 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	set_floor_color(char *line, t_parsing *p)
{
	char	*ptr;
	int		rgb[3];

	if (!line || !p)
		return (false);
	if (p->floor_color != -1)
	{
		ft_print_error("Error\nDuplicate floor color line.\n");
		return (false);
	}
	ptr = line + 1;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	ptr = ft_strtrim(ptr, "\n ");
	if (!ptr)
		return (false);
	if (!split_rgb(ptr, rgb))
	{
		free(ptr);
		return (false);
	}
	free(ptr);
	p->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (true);
}

bool	set_ceiling_color(char *line, t_parsing *p)
{
	char	*ptr;
	int		rgb[3];
	char	*trimmed;

	if (!line || !p)
		return (false);
	if (p->ceiling_color != -1)
	{
		ft_print_error("Error\nDuplicate ceiling color line.\n");
		return (false);
	}
	ptr = line + 1;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	trimmed = ft_strtrim(ptr, "\n ");
	if (!trimmed)
		return (false);
	if (!split_rgb(trimmed, rgb))
	{
		free(trimmed);
		return (false);
	}
	free(trimmed);
	p->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (true);
}
