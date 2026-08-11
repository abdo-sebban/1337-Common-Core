/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:19:26 by asebban           #+#    #+#             */
/*   Updated: 2025/02/15 13:46:19 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

void	ap_operation(char *str, t_stack **stack_a, t_stack **stack_b)
{
	if (!ft_strcmp(str, "sa\n"))
		swap_a(*stack_a, 0);
	else if (!ft_strcmp(str, "sb\n"))
		swap_b(*stack_b, 0);
	else if (!ft_strcmp(str, "ss\n"))
		swap_s(*stack_a, *stack_b);
	else if (!ft_strcmp(str, "pa\n"))
		push_a(stack_b, stack_a, 0);
	else if (!ft_strcmp(str, "pb\n"))
		push_b(stack_a, stack_b, 0);
	else if (!ft_strcmp(str, "rra\n"))
		reverse_rotate_a(stack_a, 0);
	else if (!ft_strcmp(str, "rrb\n"))
		reverse_rotate_b(stack_b, 0);
	else if (!ft_strcmp(str, "rrr\n"))
		reverse_rotate_r(stack_a, stack_b);
	else if (!ft_strcmp(str, "ra\n"))
		rotate_a(stack_a, 0);
	else if (!ft_strcmp(str, "rb\n"))
		rotate_b(stack_b, 0);
	else if (!ft_strcmp(str, "rr\n"))
		rotate_rr(stack_a, stack_b);
	else
		exit_error(stack_a, stack_b);
}

void	check_sorted(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*temp;

	if (stack_b != NULL)
	{
		ft_putstr("KO\n");
		return ;
	}
	if (!stack_a || !stack_a->next)
	{
		ft_putstr("OK\n");
		return ;
	}
	temp = stack_a;
	while (temp && temp->next)
	{
		if (temp->value > temp->next->value)
		{
			ft_putstr("KO\n");
			return ;
		}
		temp = temp->next;
	}
	ft_putstr("OK\n");
}

void	free_split_av(char **split_av)
{
	int	i;

	i = 0;
	while (split_av[i])
	{
		free(split_av[i]);
		i++;
	}
	free(split_av);
}

void	read_from_stdin(t_stack **stack_a, t_stack **stack_b)
{
	char	*str;

	str = get_next_line(0);
	while (str)
	{
		ap_operation(str, stack_a, stack_b);
		free(str);
		str = get_next_line(0);
	}
	check_sorted(*stack_a, *stack_b);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**split_av;
	int		i;

	i = 1;
	if (ac < 2)
		return (0);
	while (i < ac)
		if (is_empty(av[i++]))
			exit_error(NULL, NULL);
	split_av = handl_av(av);
	if (!split_av)
		exit_error(NULL, NULL);
	if (!is_correct_input(split_av))
		exit_error(NULL, NULL);
	stack_b = NULL;
	stack_a = fill_stack_values(ft_strlen_stack(split_av), split_av);
	free_split_av(split_av);
	read_from_stdin(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
