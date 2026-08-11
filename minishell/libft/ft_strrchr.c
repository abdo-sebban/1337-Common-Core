/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:03:29 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/15 13:29:28 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i--;
	}
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	return (0);
}

int	merged_token_len(const char *s, char sep)
{
	int		len;
	char	qc;

	len = 0;
	while (s[len] && s[len] != sep && !is_heredoc(s + len))
	{
		if (s[len] == '\'' || s[len] == '"')
		{
			qc = s[len++];
			while (s[len] && s[len] != qc)
				len++;
			if (s[len] == qc)
				len++;
		}
		else
			len++;
	}
	return (len);
}
