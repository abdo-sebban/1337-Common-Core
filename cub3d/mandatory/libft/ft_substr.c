/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:57:16 by asebban           #+#    #+#             */
/*   Updated: 2024/11/04 13:08:22 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_empty_string(void)
{
	char	*ptr;

	ptr = malloc(1);
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	return (ptr);
}

static size_t	calculate_length(size_t str_len, unsigned int start, size_t len)
{
	if (start + len > str_len)
		return (str_len - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (allocate_empty_string());
	len = calculate_length(str_len, start, len);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
