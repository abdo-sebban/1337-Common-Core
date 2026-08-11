/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:35:31 by asebban           #+#    #+#             */
/*   Updated: 2025/02/23 14:30:19 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 999999999
# endif

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

int			is_sign(char c);
int			nbstr_cmp(const char *s1, const char *s2);
char		**ft_split(const char *s, char c);
int			is_digit(char c);
char		*get_next_line(int fd);
char		*ft_strdup(char *s);
size_t		ft_strlen(char *s);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
void		fill_string(char *res, char *s1, char *s2);
void		push_a(t_stack **stack_b, t_stack **stack_a, int msg);
void		push_b(t_stack **stack_a, t_stack **stack_b, int msg);
void		reverse_rotate_a(t_stack **stack_a, int msg);
void		reverse_rotate_b(t_stack **stack_b, int msg);
void		reverse_rotate_r(t_stack **stack_a, t_stack **stack_b);
void		rotate_a(t_stack **stack_a, int msg);
void		rotate_b(t_stack **stack_b, int msg);
void		rotate_rr(t_stack **stack_a, t_stack **stack_b);
void		swap_a(t_stack *stack_a, int msg);
void		swap_b(t_stack *stack_b, int msg);
void		swap_s(t_stack *stack_a, t_stack *stack_b);
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr(char *str);
long int	ft_atoi(const char *str);
size_t		ft_strlen_stack(char **str);
int			get_stack_size(t_stack	*stack);
void		exit_error(t_stack **stack_a, t_stack **stack_b);
char		**handl_av(char **av);
int			is_correct_input(char **split_av);
t_stack		*fill_stack_values(int size, char **split_av);
int			is_empty(char *str);
int			get_stack_size(t_stack *stack);
void		assign_index(t_stack *stack_a, int size);
void		free_stack(t_stack **stack);
t_stack		*get_stack_bottom(t_stack *stack);
t_stack		*get_stack_before_bottom(t_stack *stack);
void		stack_add_bottom(t_stack **stack, t_stack *new);
void		assign_index(t_stack *stack_a, int stack_size);
t_stack		*fill_stack_values(int ac, char **av);
void		free_stack(t_stack **stack);
char		*get_next_line(int fd);
t_stack		*stack_new(int value);

#endif
