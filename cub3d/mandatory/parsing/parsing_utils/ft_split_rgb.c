/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:13:34 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:13:34 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_str_isnumeric(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (false);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static	bool	validate_rgb_count(char **parts)
{
	int	count;
	int	i;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		ft_print_error("Error\nRGB must have exactly 3 values\n");
		ft_free_split(parts);
		return (false);
	}
	i = 0;
	while (i < 3)
	{
		if (parts[i][0] == '\0')
		{
			ft_print_error("Error\nRGB contains empty value\n");
			ft_free_split(parts);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	parse_single_rgb_value(char *part, int *out_value, char **parts)
{
	long	val;
	int		i;

	i = 0;
	if (!part || *part == '\0')
		return (ft_print_error("Error\nEmpty RGB value\n"), \
ft_free_split(parts), false);
	while (part[i])
	{
		if (part[i] == ' ' || part[i] == '\t' || part[i] == '\n')
			return (ft_print_error("Error\nRGB value contains \
spaces or tabs\n"), ft_free_split(parts), false);
		i++;
	}
	if (!ft_str_isnumeric(part))
		return (ft_print_error("Error\nNon numeric RGB \
value\n"), ft_free_split(parts), false);
	val = ft_atoi(part);
	if (val < 0 || val > 255)
		return (ft_print_error("Error\nRGB value out of range \
(0,255)\n"), ft_free_split(parts), false);
	*out_value = (int)val;
	return (true);
}

bool	split_rgb(const char *s, int rgb[3])
{
	char	**parts;
	int		i;

	if (!s || !rgb)
		return (false);
	parts = ft_split(s, ',');
	if (!parts)
		return (false);
	if (!validate_rgb_count(parts))
		return (false);
	i = 0;
	while (i < 3)
	{
		if (!parse_single_rgb_value(parts[i], &rgb[i], parts))
			return (false);
		i++;
	}
	ft_free_split(parts);
	return (true);
}
