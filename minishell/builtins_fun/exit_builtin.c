/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:11:51 by asebban           #+#    #+#             */
/*   Updated: 2025/05/16 14:50:45 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static	int	skip_ws_and_sign(const char *s, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	while (s[i] && ft_isspace((unsigned char)s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static	int	parse_digits_with_limit(const char *s,
		int start, unsigned long limit, unsigned long *out_acc)
{
	unsigned long	acc;
	int				i;
	int				digit;

	acc = 0;
	i = start;
	if (!ft_isdigit(s[i]))
		return (-1);
	while (ft_isdigit(s[i]))
	{
		digit = s[i] - '0';
		if (acc > limit / 10
			|| (acc == limit / 10 && (unsigned long)digit > (limit % 10)))
			return (-1);
		acc = acc * 10 + digit;
		i++;
	}
	*out_acc = acc;
	return (i);
}

static	bool	is_arg_number(const char *arg)
{
	int				sign;
	unsigned long	acc;
	unsigned long	limit;
	int				idx;

	idx = skip_ws_and_sign(arg, &sign);
	if (sign < 0)
		limit = -(unsigned long)(LONG_MIN);
	else
		limit = (unsigned long)LONG_MAX;
	idx = parse_digits_with_limit(arg, idx, limit, &acc);
	if (idx < 0)
		return (false);
	while (arg[idx] && isspace((unsigned char)arg[idx]))
		idx++;
	return (arg[idx] == '\0');
}

int	exit_builtin(t_shell *shell, char **args, int in_pipe)
{
	int		arg_count;
	int		exit_code;
	int		tmp;

	exit_code = exit_status(0, 0);
	arg_count = count_args(args);
	handle_no_args(shell, exit_code, arg_count, in_pipe);
	if (!is_arg_number(args[1]))
		return (handle_non_numeric(args[1], shell, in_pipe));
	tmp = handle_too_many(arg_count, in_pipe);
	if (tmp != -1)
		return (tmp);
	print_exit_if_needed(in_pipe);
	exit_code = ft_atoi(args[1]);
	clean_exit(shell, exit_code);
	return (EXIT_SUCCESS);
}
