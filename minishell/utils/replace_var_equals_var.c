/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_equals_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:52:22 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 13:51:59 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	var_name_len1(const char *seg, int pos)
{
	int	len;

	len = 0;
	while (seg[pos + len] && (ft_isalnum(seg[pos + len]) || \
			seg[pos + len] == '_'))
		len++;
	return (len);
}

char	*replace_var_equals_var(char *input, t_shell *shell)
{
	char	**tokens;
	char	*output;

	if (!input || !shell)
		return (NULL);
	tokens = ft_split_heredoc(input, ' ');
	if (!tokens)
		return (NULL);
	output = process_tokens(tokens, shell);
	return (output);
}
