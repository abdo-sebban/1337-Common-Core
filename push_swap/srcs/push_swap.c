/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:54:40 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 13:57:35 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack->next != NULL)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	push_swap(t_stack **stack_a, t_stack **stack_b, int stack_size)
{
	if (stack_size == 2 && !is_sorted(*stack_a))
		swap_a(stack_a);
	else if (stack_size == 3)
		tiny_sort(stack_a);
	else if (stack_size > 3 && !is_sorted(*stack_a))
		sort(stack_a, stack_b);
}

static void	free_split(char **split_av)
{
	int	i;

	i = 0;
	while (split_av[i])
		free(split_av[i++]);
	free(split_av);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		stack_size;
	char	**split_av;
	int		i;

	if (ac < 2)
		return (0);
	i = 1;
	while (i < ac)
		if (is_empty(av[i++]))
			exit_error(NULL, NULL);
	split_av = handl_av(av);
	if (!split_av)
		exit_error(NULL, NULL);
	if (!is_correct_input(split_av))
		exit_error(NULL, NULL);
	stack_b = NULL;
	i = ft_strlen_stack(split_av);
	stack_a = fill_stack_values(i, split_av);
	free_split(split_av);
	stack_size = get_stack_size(stack_a);
	assign_index(stack_a, stack_size + 1);
	push_swap(&stack_a, &stack_b, stack_size);
	return (free_stack(&stack_a), free_stack(&stack_b), 0);
}
