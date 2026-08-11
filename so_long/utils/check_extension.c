/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:18:05 by asebban           #+#    #+#             */
/*   Updated: 2025/02/23 09:49:25 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	int	check_ext_file(char *file)
{
	int	len;

	if (file == NULL)
		return (0);
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".ber") != 0)
		return (0);
	return (1);
}

int	handle_errors(int ac, char *file)
{
	if (ac != 2)
	{
		ft_printf("Error\nInvalid number of arguments!\n");
		return (1);
	}
	if (!check_ext_file(file))
	{
		ft_printf("Invalid extension !!\n");
		return (1);
	}
	return (0);
}
