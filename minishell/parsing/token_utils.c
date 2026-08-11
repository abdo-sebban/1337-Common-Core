/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:32:46 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 18:00:43 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_input_array(char **input_array)
{
	int	size;

	size = 0;
	if (!input_array)
		return (0);
	while (input_array[size])
		size++;
	return (size);
}

t_lexer_list	*create_lexer_list(char **input_array)
{
	int	size;

	size = count_input_array(input_array);
	if (size == 0)
		return (NULL);
	return (allocate_lexer_nodes(size));
}

int	find_token_pos(const char *rl, const char *s, int last_pos)
{
	size_t	rl_len;
	size_t	rem_len;
	char	*p;

	if (!rl || !s)
		return (-1);
	rl_len = ft_strlen(rl);
	if ((size_t)last_pos >= rl_len)
		return (-1);
	rem_len = rl_len - last_pos;
	p = ft_strnstr(rl + last_pos, s, rem_len);
	if (!p)
		return (-1);
	return ((int)(p - rl));
}

t_token	which_type(char *s, int inside)
{
	if (!s)
		return (0);
	if (inside)
		return (CMD);
	if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	if (ft_strcmp(s, "<") == 0)
		return (REDERECT_IN);
	if (ft_strcmp(s, ">") == 0)
		return (rederect_out);
	if (ft_strcmp(s, "<<") == 0)
	{
		return (HEREDOC);
	}
	if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	return (CMD);
}
