/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_val_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:06:34 by asebban           #+#    #+#             */
/*   Updated: 2025/05/11 17:08:00 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lookup_and_append(const char *name_buf,
	char *out, t_replinfo *info, t_shell *shell)
{
	char	*val;

	val = get_env_value(shell->env, (char *)name_buf);
	if (val)
		info->o = buf_append(out, info->o, val);
}

size_t	handle_alpha_case(const char *input,
	char *out, t_replinfo *info, t_shell *shell)
{
	char	name[256];

	extract_var_name(input, info, name);
	lookup_and_append(name, out, info, shell);
	return (info->i);
}
