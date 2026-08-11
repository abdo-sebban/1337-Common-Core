/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:26:31 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 15:55:29 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	var_name_len(const char *seg, int pos)
{
	int	len;

	len = 0;
	while (seg[pos + len] && (ft_isalnum(seg[pos + len])
			|| seg[pos + len] == '_'))
		len++;
	return (len);
}

static	int	var_value_len(const char *seg, t_shell *shell, int *i)
{
	int		start;
	int		name_len;
	char	*key;
	char	*value;
	int		val_len;

	start = *i + 1;
	name_len = var_name_len(seg, start);
	key = ft_malloc(name_len + 1, 1);
	if (!key)
		return (-1);
	ft_strncpy(key, seg + start, name_len);
	key[name_len] = '\0';
	value = get_env_value(shell->env, key);
	if (value)
		val_len = ft_strlen(value);
	else
		val_len = 0;
	*i = start + name_len;
	return (val_len);
}

int	all_value(char *seg, t_shell *shell)
{
	int	i;
	int	total;
	int	len;

	i = 0;
	total = 0;
	if (!seg || !shell)
		return (0);
	while (seg[i])
	{
		if (seg[i] == '$' && (ft_isalpha(seg[i + 1]) || seg[i + 1] == '_'))
		{
			len = var_value_len(seg, shell, &i);
			if (len < 0)
				return (-1);
			total += len;
		}
		else
			i++;
	}
	return (total + 250);
}
