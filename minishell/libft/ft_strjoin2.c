/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:21:01 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 13:36:26 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	full_var(char *s1, char *s2, size_t *l1, size_t *l2)
{
	if (s1)
		*l1 = ft_strlen (s1);
	else
		*l1 = 0;
	if (s2)
		*l2 = ft_strlen (s2);
	else
		*l2 = 0;
}

char	*ft_strjoin2(char *s1, char *s2, int to_free)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	(void)to_free;
	full_var(s1, s2, &len1, &len2);
	res = ft_malloc(len1 + len2 + 1, 1);
	if (!res)
		return (NULL);
	if (s1)
		ft_strcpy(res, s1);
	else
		res[0] = '\0';
	if (s2)
		ft_strcat(res, s2);
	res[len1 + len2] = '\0';
	to_free = 0;
	return (res);
}
