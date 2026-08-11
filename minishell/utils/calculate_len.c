/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:26:26 by asebban           #+#    #+#             */
/*   Updated: 2025/05/09 18:34:50 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	bool	toggle_single_quote(char c,
				bool in_double, bool *in_single)
{
	if (c == '\'' && in_double == false)
	{
		*in_single = !(*in_single);
		return (true);
	}
	return (false);
}

static	bool	toggle_double_quote(char c,
				bool in_single, bool *in_double)
{
	if (c == '"' && in_single == false)
	{
		*in_double = !(*in_double);
		return (true);
	}
	return (false);
}

static	int	handle_variable(const char *str,
			int *i, t_shell *shell)
{
	char	var_name[PATH_MAX];
	int		k;
	char	*value;

	k = 0;
	(*i)++;
	while ((ft_isalnum(str[*i]) || str[*i] == '_')
		&& k < PATH_MAX - 1)
	{
		var_name[k++] = str[*i];
		(*i)++;
	}
	var_name[k] = '\0';
	value = get_env_value(shell->env, var_name);
	if (value != NULL)
		return ((int)ft_strlen(value));
	return (0);
}

static	int	handle_regular(int *i)
{
	(*i)++;
	return (1);
}

int	calculate_max_len(const char *str, t_shell *shell)
{
	int		i;
	int		len;
	bool	in_single;
	bool	in_double;

	i = 0;
	len = 0;
	in_single = false;
	in_double = false;
	while (str && str[i])
	{
		if (toggle_single_quote(str[i], in_double, &in_single)
			|| toggle_double_quote(str[i], in_single, &in_double))
		{
			len++;
			i++;
		}
		else if (in_single == false && str[i] == '$'
			&& str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_'))
			len += handle_variable(str, &i, shell);
		else
			len += handle_regular(&i);
	}
	return (len);
}
