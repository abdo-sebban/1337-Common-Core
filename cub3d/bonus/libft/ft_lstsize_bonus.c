/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:49:29 by asebban           #+#    #+#             */
/*   Updated: 2024/11/04 13:10:30 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*start;

	len = 0;
	start = lst;
	if (!lst)
	{
		return (0);
	}
	while (start)
	{
		len++;
		start = start->next;
	}
	return (len);
}
