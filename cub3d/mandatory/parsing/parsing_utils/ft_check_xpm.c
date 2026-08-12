/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:15 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:15 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	file_has_xpm_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (false);
	len = ft_strlen(path);
	if (len < 4)
		return (false);
	if (ft_strncmp(path + (len - 4), ".xpm", 4) == 0)
		return (true);
	else
		return (false);
}
