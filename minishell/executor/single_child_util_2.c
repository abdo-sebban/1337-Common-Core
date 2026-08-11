/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_child_util_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:36:12 by asebban           #+#    #+#             */
/*   Updated: 2025/05/23 16:46:47 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	get_size_environ(t_environ_node *current)
{
	int	size;

	size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

static	char	**create_environ_array(t_environ_list *env)
{
	char	**environ_array;
	int		size;

	if (!env || !env->head)
		return (NULL);
	size = get_size_environ(env->head);
	environ_array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!environ_array)
		return (NULL);
	return (environ_array);
}

static	void	transform_error(char **environ_array)
{
	int	i;

	if (!environ_array)
		return ;
	i = 0;
	while (environ_array[i])
		i++;
}

static	void	transform_helper(t_environ_node *current, char **environ_array)
{
	int		i;
	char	*env_str;
	char	*temp;

	i = 0;
	while (current != NULL)
	{
		if (current->value == NULL)
		{
			current = current->next;
			continue ;
		}
		temp = ft_strjoin(current->key, "=");
		if (!temp)
			return (transform_error(environ_array));
		env_str = ft_strjoin(temp, current->value);
		if (!env_str)
			return (transform_error(environ_array));
		environ_array[i] = env_str;
		i++;
		current = current->next;
	}
	environ_array[i] = NULL;
}

char	**transform_environ_array(t_shell *shell)
{
	char			**environ_array;
	t_environ_node	*current;

	if (!shell || !shell->env)
		return (NULL);
	if (!shell->env->head)
		handle_no_file_error();
	current = shell->env->head;
	environ_array = create_environ_array(shell->env);
	transform_helper(current, environ_array);
	if (!environ_array[0])
		return (NULL);
	return (environ_array);
}
