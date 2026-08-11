/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:13:33 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/15 12:55:38 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_environ_list *env)
{
	char			*buf;
	t_environ_node	*node;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		node = ft_getenv(env, "PWD");
		if (!node || !node->value)
			return (printf("%s\n", save_pwd(0, NULL)));
		printf("%s\n", node->value);
	}
	else
	{
		printf("%s\n", buf);
		free(buf);
	}
	return (0);
}
