/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_rl_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:45:15 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 17:58:49 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static	char	*replace_with_clean(char *rl_copy, size_t start, size_t end)
{
	char	*new_str;
	size_t	i;

	if (end < start || !rl_copy)
		return (NULL);
	new_str = ft_malloc(sizeof(char) * (end - start + 2), 1);
	if (!new_str)
		return (perror("minishell"), NULL);
	i = 0;
	while (start <= end)
		new_str[i++] = rl_copy[start++];
	new_str[i] = '\0';
	return (new_str);
}

char	*clean_rl_copy(char *rl_copy)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (!rl_copy)
		return (NULL);
	len = ft_strlen(rl_copy);
	start = 0;
	while (rl_copy[start] && ft_isspace(rl_copy[start]))
		start++;
	if (start == len)
		return (ft_strdup(""));
	end = len - 1;
	while (end > start && ft_isspace(rl_copy[end]))
		end--;
	return (replace_with_clean(rl_copy, start, end));
}
