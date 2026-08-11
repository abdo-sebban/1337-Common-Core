/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:17:10 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 10:07:15 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

size_t	ft_strlen_stack(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
