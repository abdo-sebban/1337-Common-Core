/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:08:16 by asebban           #+#    #+#             */
/*   Updated: 2025/05/12 11:12:16 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_expand_variable(const char *in,
	char **res, int *i, t_shell *shell)
{
	char	*val;
	int		start;
	int		len;

	if (in[*i + 1] == '?')
	{
		val = ft_itoa(exit_status(EXIT_GET, 0));
		*res = ft_strjoin(*res, val);
		*i += 2;
		return (1);
	}
	start = *i + 1;
	len = 0;
	while (ft_isalnum(in[start + len]) || in[start + len] == '_')
		len++;
	val = get_env_value2(ft_substr(in, start, len), shell);
	*res = ft_strjoin(*res, val);
	*i = start + len;
	return (1);
}

char	*ft_strtrim1(const char *s1)
{
	return (ft_strtrim(s1, " \t\n"));
}

char	*get_env_value2(const char *key, t_shell *shell)
{
	t_environ_node	*node;
	char			*copy;

	if (!key || !shell || !shell->env)
		return (ft_strdup(""));
	node = shell->env->head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			copy = ft_strdup(node->value);
			if (copy)
				return (copy);
			return (ft_strdup(" "));
		}
		node = node->next;
	}
	return (ft_strdup(""));
}

void	append_char(char **res, const char *src, int len)
{
	char	*tmp;

	tmp = ft_strjoin(*res, ft_substr(src, 0, len));
	*res = tmp;
}

char	*replace_vars1(const char *input, t_shell *shell)
{
	return (segment_expand(input, shell));
}
