/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:42:54 by asebban           #+#    #+#             */
/*   Updated: 2025/05/16 11:31:48 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	token_len(const char *s, char sep)
{
	if (is_heredoc(s))
		return (2);
	return (merged_token_len(s, sep));
}

static	int	count_tokens1(const char *s, char sep)
{
	int	i;
	int	cnt;
	int	len;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if (!s[i])
			break ;
		cnt++;
		len = token_len(s + i, sep);
		i += len;
	}
	return (cnt);
}

static	char	*next_token(const char *s, int *ip, char sep)
{
	int		start;
	int		len;
	char	*tok;

	while (s[*ip] && s[*ip] == sep)
		(*ip)++;
	if (!s[*ip])
		return (NULL);
	start = *ip;
	len = token_len(s + start, sep);
	tok = ft_strndup1(s + start, len);
	*ip += len;
	return (tok);
}

char	**ft_split_heredoc(const char *s, char sep)
{
	int		total;
	char	**arr;
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (!s)
		return (NULL);
	total = count_tokens1(s, sep);
	arr = ft_malloc((sizeof(*arr) * (total + 1)), 1);
	if (!arr)
		return (NULL);
	while (k < total)
	{
		arr[k] = next_token(s, &i, sep);
		if (!arr[k])
			break ;
		k++;
	}
	arr[k] = NULL;
	return (arr);
}
