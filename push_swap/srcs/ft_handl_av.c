/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handl_av.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:54:08 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 14:58:24 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static	char	*handl_av_aid(char **av)
{
	char	*str;
	int		i;
	char	*tmp;

	str = ft_strdup("");
	if (!str)
		exit_error(NULL, NULL);
	i = 1;
	while (av[i])
	{
		tmp = str;
		str = ft_strjoin(str, av[i]);
		if (!str)
			(free(tmp), exit_error(NULL, NULL));
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, " ");
		if (!str)
			(free(tmp), exit_error(NULL, NULL));
		free(tmp);
		i++;
	}
	return (str);
}

char	**handl_av(char **av)
{
	char	*str;
	char	**split_av;

	str = handl_av_aid(av);
	split_av = ft_split(str, ' ');
	if (!split_av)
		return (free(str), NULL);
	return (free(str), split_av);
}
