/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:20:56 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 10:07:53 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

void	reverse_rotate_a(t_stack **stack_a, int msg)
{
	t_stack	*tmp;
	t_stack	*stack_bottom;
	t_stack	*before_stack_bottom;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	stack_bottom = get_stack_bottom(*stack_a);
	before_stack_bottom = get_stack_before_bottom(*stack_a);
	if (stack_bottom == NULL || before_stack_bottom == NULL)
		return ;
	tmp = *stack_a;
	*stack_a = stack_bottom;
	(*stack_a)->next = tmp;
	before_stack_bottom->next = NULL;
	if (msg == 1)
		ft_putstr("rra\n");
}

void	reverse_rotate_b(t_stack **stack_b, int msg)
{
	t_stack	*tmp;
	t_stack	*stack_bottom;
	t_stack	*before_stack_bottom;

	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	stack_bottom = get_stack_bottom(*stack_b);
	before_stack_bottom = get_stack_before_bottom(*stack_b);
	if (stack_bottom == NULL || before_stack_bottom == NULL)
		return ;
	tmp = *stack_b;
	*stack_b = stack_bottom;
	(*stack_b)->next = tmp;
	before_stack_bottom->next = NULL;
	if (msg == 1)
		ft_putstr("rrb\n");
}

void	reverse_rotate_r(t_stack **stack_a, t_stack **stack_b)
{
	reverse_rotate_a(stack_a, 0);
	reverse_rotate_b(stack_b, 0);
}
