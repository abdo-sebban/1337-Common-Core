/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:14:49 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 19:36:49 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size_to_copy;

	if (new_size == 0)
		return (NULL);
	new_ptr = ft_malloc(new_size, 1);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			size_to_copy = old_size;
		else
			size_to_copy = new_size;
		ft_memcpy(new_ptr, ptr, size_to_copy);
	}
	return (new_ptr);
}

static	int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static	int	skip_empty_token(const char *cmdline, int *idx)
{
	int	i;

	i = *idx;
	if (ft_isspace((unsigned char)cmdline[i]))
	{
		(*idx)++;
		return (1);
	}
	if (cmdline[i] == '"' && cmdline[i + 1] == '"')
	{
		*idx += 2;
		return (1);
	}
	if (cmdline[i] == '\'' && cmdline[i + 1] == '\'')
	{
		*idx += 2;
		return (1);
	}
	if (cmdline[i] == '.' && cmdline[i + 1] == '.')
	{
		*idx += 2;
		return (1);
	}
	return (0);
}

int	is_cmdline_empty(const char *cmdline)
{
	int	i;

	if (!cmdline)
		return (1);
	i = 0;
	while (cmdline[i])
	{
		if (skip_empty_token(cmdline, &i))
			continue ;
		return (0);
	}
	return (1);
}
