/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_hard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:26:18 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 16:18:41 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	bool	check_if_first_is_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (ft_strncmp(str + i, "export", 6) != 0)
		return (false);
	i += 6;
	return (str[i] == '\0' || str[i] == ' ' || str[i] == '\t');
}

static	size_t	compute_size(char **strs, size_t *count)
{
	size_t	total;
	size_t	c;

	if (!strs || !*strs)
		return (0);
	total = 0;
	c = 0;
	while (strs[c])
	{
		total += ft_strlen(strs[c]);
		c++;
	}
	if (c > 1)
		total += (c - 1);
	total += 1;
	*count = c;
	return (total);
}

char	*join_strings(char **strs, char delim)
{
	size_t	size;
	size_t	count;
	char	*buf;
	size_t	i;
	size_t	len;

	1 && (len = 0, size = compute_size(strs, &count));
	if (size == 0)
		return (NULL);
	buf = ft_malloc(size, 1);
	if (!buf)
		return (NULL);
	1 && (buf[0] = '\0', i = 0);
	while (i < count)
	{
		ft_strcat(buf, strs[i]);
		if (i + 1 < count)
		{
			len = ft_strlen(buf);
			buf[len] = delim;
			buf[len + 1] = '\0';
		}
		i++;
	}
	return (buf);
}

char	*export_hard(char *str, t_shell *shell)
{
	char	**arr;
	int		i;
	char	*result;
	char	*expanded;

	i = 0;
	arr = ft_split1(str, '|');
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		if (check_if_first_is_export(arr[i]))
		{
			expanded = change_all_var(arr[i], shell);
			if (expanded)
				arr[i] = expanded;
		}
		i++;
	}
	result = join_strings(arr, '|');
	return (result);
}
