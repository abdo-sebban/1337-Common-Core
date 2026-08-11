/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:08:06 by asebban           #+#    #+#             */
/*   Updated: 2025/05/16 15:23:47 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	calculate_total_length(const char *seg, t_shell *shell)
{
	if (!seg || !shell)
		return (0);
	return (ft_strlen(seg) + all_value((char *)seg, shell) + 1);
}

char	*ft_replace_var3(const char *seg, t_shell *shell, int flag)
{
	int		total;
	char	*result;

	if (!seg || !shell)
		return (NULL);
	total = calculate_total_length(seg, shell);
	if (total <= 0)
		return (NULL);
	result = ft_malloc(total, 1);
	if (!result)
		return (NULL);
	fill_replaced_segment(seg, shell, result, flag);
	return (result);
}
