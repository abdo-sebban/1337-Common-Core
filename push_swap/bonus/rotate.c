/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:08:56 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 10:07:55 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

void	rotate_a(t_stack **stack_a, int msg)
{
	t_stack	*tmp;
	t_stack	*stack_bottom;

	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	stack_bottom = get_stack_bottom(*stack_a);
	tmp->next = NULL;
	stack_bottom->next = tmp;
	if (msg == 1)
		ft_putstr("ra\n");
}

void	rotate_b(t_stack **stack_b, int msg)
{
	t_stack	*tmp;
	t_stack	*stack_bottom;

	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	stack_bottom = get_stack_bottom(*stack_b);
	tmp->next = NULL;
	stack_bottom->next = tmp;
	if (msg == 1)
		ft_putstr("rb\n");
}

void	rotate_rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate_a(stack_a, 0);
	rotate_b(stack_b, 0);
}
