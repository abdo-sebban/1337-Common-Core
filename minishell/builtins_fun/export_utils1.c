/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:41:04 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 17:59:18 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_export_data	parse_export_str(const char *str)
{
	t_export_data	data;
	char			*eq;

	data.key = NULL;
	data.value = NULL;
	data.append = false;
	eq = ft_strchr(str, '=');
	if (eq && eq > str && *(eq - 1) == '+')
	{
		data.append = true;
		data.key = ft_substr(str, 0, (eq - str) - 1);
		data.value = ft_strdup(eq + 1);
	}
	else if (eq)
	{
		data.key = ft_substr(str, 0, eq - str);
		data.value = ft_strdup(eq + 1);
	}
	else
	{
		data.key = ft_strdup(str);
		data.value = NULL;
	}
	return (data);
}

void	update_node(t_environ_node *node, t_export_data *data)
{
	char	*new_val;

	if (!data->value)
		return ;
	if (data->append && node->value)
	{
		new_val = ft_strjoin(node->value, data->value);
		node->value = new_val;
	}
	else
		node->value = data->value;
}

void	add_new_node(t_shell *shell, t_export_data *data)
{
	t_environ_node	*node;
	char			*temp;
	char			*full;

	if (data->value)
	{
		temp = ft_strjoin(data->key, "=");
		full = ft_strjoin(temp, data->value);
		node = create_environ_node(full);
	}
	else
	{
		node = ft_malloc(sizeof(t_environ_node), 1);
		node->key = ft_strdup(data->key);
		node->value = NULL;
		node->next = NULL;
	}
	add_back_environ_node(shell->env, node);
}

void	exporting(t_shell *shell, char *str)
{
	t_export_data	data;
	t_environ_node	*node;

	data = parse_export_str(str);
	node = get_node(shell->env, data.key);
	if (node)
		update_node(node, &data);
	else
		add_new_node(shell, &data);
}

int	export_args(t_shell *shell, char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = EXIT_SUCCESS;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: not a \
valid identifier\n", STDERR_FILENO);
			ret = EXIT_FAILURE;
			exit_status(1, 1);
			continue ;
		}
		exporting(shell, args[i]);
	}
	return (ret);
}
