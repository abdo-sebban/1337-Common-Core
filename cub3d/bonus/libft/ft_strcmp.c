/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:08:09 by asebban           #+#    #+#             */
/*   Updated: 2025/08/04 11:33:07 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	uc1;
	unsigned char	uc2;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	uc1 = (unsigned char)s1[i];
	uc2 = (unsigned char)s2[i];
	return ((int)(uc1 - uc2));
}
