/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:56:06 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/21 12:02:16 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cat(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen (str) - 1;
	while (str[len] && str[len] != '/')
	{
		i++;
		len--;
	}
	ft_bzero(str + len, i);
}
