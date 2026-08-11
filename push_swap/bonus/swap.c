/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:52:55 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 10:08:02 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

void	swap_a(t_stack *stack_a, int msg)
{
	int	tmp;

	if (stack_a == NULL || stack_a->next == NULL)
		return ;
	tmp = stack_a->value;
	stack_a->value = stack_a->next->value;
	stack_a->next->value = tmp;
	tmp = stack_a->index;
	stack_a->index = stack_a->next->index;
	stack_a->next->index = tmp;
	if (msg == 1)
		ft_putstr("sa\n");
}

void	swap_b(t_stack *stack_b, int msg)
{
	int	tmp;

	if (stack_b == NULL || stack_b->next == NULL)
		return ;
	tmp = stack_b->value;
	stack_b->value = stack_b->next->value;
	stack_b->next->value = tmp;
	tmp = stack_b->index;
	stack_b->index = stack_b->next->index;
	stack_b->next->index = tmp;
	if (msg == 1)
		ft_putstr("sb\n");
}

void	swap_s(t_stack *stack_a, t_stack *stack_b)
{
	swap_a(stack_a, 0);
	swap_b(stack_b, 0);
}
