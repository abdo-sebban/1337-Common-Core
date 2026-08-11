/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_soh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:53:48 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 10:56:23 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_soh_with_dollar_in_env(t_environ_list *env_list)
{
	t_environ_node	*current;
	char			*value_ptr;

	current = env_list->head;
	while (current != NULL)
	{
		value_ptr = current->value;
		while (value_ptr != NULL && *value_ptr != '\0')
		{
			if (*value_ptr == '\x01')
			{
				*value_ptr = '$';
			}
			value_ptr++;
		}
		current = current->next;
	}
}

void	replace_soh_with_dollar(char *str)
{
	char	*p;

	p = str;
	while (p && *p)
	{
		if (*p == '\x01')
		{
			*p = '$';
		}
		p++;
	}
}
