/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler_multi.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:07:19 by asebban           #+#    #+#             */
/*   Updated: 2025/05/08 16:13:09 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*path_join(const char *dir, const char *file)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, file);
	return (full);
}

static char	*is_direct_path(t_executor *current)
{
	struct stat	st;

	if (current->execs[0][0] == '/' || current->execs[0][0] == '.')
	{
		if (stat(current->execs[0], &st) == 0)
			return (ft_strdup(current->execs[0]));
		return (NULL);
	}
	return (NULL);
}

static char	*search_in_path(t_executor *current)
{
	struct stat	st;
	char		*candidate;
	int			i;

	i = 0;
	if (!current->path)
		return (NULL);
	while (current->path[i])
	{
		candidate = path_join(current->path[i], current->execs[0]);
		if (!candidate)
			return (NULL);
		if (stat(candidate, &st) == 0)
			return (candidate);
		i++;
	}
	return (NULL);
}

static char	*search_in_dot(t_executor *current)
{
	struct stat	st;
	size_t		len;
	char		*dotcmd;

	len = 2 + ft_strlen(current->execs[0]) + 1;
	dotcmd = ft_malloc(len, 1);
	if (!dotcmd)
		return (NULL);
	ft_memcpy(dotcmd, "./", 2);
	ft_memcpy(dotcmd + 2, current->execs[0], ft_strlen(current->execs[0]) + 1);
	if (stat(dotcmd, &st) == 0)
		return (dotcmd);
	return (NULL);
}

char	*execute_other_helper(t_executor *current)
{
	char	*result;

	result = is_direct_path(current);
	if (result)
		return (result);
	result = search_in_path(current);
	if (result)
		return (result);
	if (!current->path)
		return (search_in_dot(current));
	return (NULL);
}
