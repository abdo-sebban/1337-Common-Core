/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:42:20 by asebban           #+#    #+#             */
/*   Updated: 2025/05/20 18:03:26 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_herdoc(int action)
{
	static int	status;

	if (action == 0)
		return (status);
	else if (action == 1)
		status += 1;
	else if (action == 2)
		status = 0;
	return (status);
}
