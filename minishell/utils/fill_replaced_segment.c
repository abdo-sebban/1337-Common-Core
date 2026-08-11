/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_replaced_segment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:37:30 by asebban           #+#    #+#             */
/*   Updated: 2025/05/16 15:24:38 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_segstate
{
	int		ptrs[3];
	bool	q[2];
}	t_segstate;

static void	init_state(t_segstate *state, int flag)
{
	state->ptrs[0] = 0;
	state->ptrs[1] = 0;
	state->ptrs[2] = flag;
	state->q[0] = false;
	state->q[1] = false;
}

static bool	handle_heredoc(const char *seg, char *result, t_segstate *state)
{
	if (seg[state->ptrs[0]] == '<' && seg[state->ptrs[0] + 1] == '<')
	{
		state->ptrs[2] = 1;
		result[state->ptrs[1]++] = seg[state->ptrs[0]++];
		result[state->ptrs[1]++] = seg[state->ptrs[0]++];
		return (true);
	}
	return (false);
}

static bool	handle_quotes(const char *seg, char *result, t_segstate *state)
{
	char	c;

	c = seg[state->ptrs[0]];
	if (c == '\'' && !state->q[1])
	{
		state->q[0] = !state->q[0];
		result[state->ptrs[1]++] = seg[state->ptrs[0]++];
		return (true);
	}
	else if (c == '"' && !state->q[0])
	{
		state->q[1] = !state->q[1];
		result[state->ptrs[1]++] = seg[state->ptrs[0]++];
		return (true);
	}
	return (false);
}

static bool	handle_variable(const char *seg,
		t_shell *shell, char *result, t_segstate *state)
{
	if (!state->q[0] && seg[state->ptrs[0]] == '$'
		&& (ft_isalpha(seg[state->ptrs[0] + 1])
			|| seg[state->ptrs[0] + 1] == '_'))
	{
		append_var(seg, shell, result, state->ptrs);
		return (true);
	}
	return (false);
}

void	fill_replaced_segment(const char *seg,
	t_shell *shell, char *result, int flag)
{
	t_segstate	state;

	init_state(&state, flag);
	while (seg[state.ptrs[0]])
	{
		if (!state.q[0] && handle_heredoc(seg, result, &state))
			continue ;
		if (handle_quotes(seg, result, &state))
			continue ;
		if (handle_variable(seg, shell, result, &state))
			continue ;
		result[state.ptrs[1]++] = seg[state.ptrs[0]++];
	}
	result[state.ptrs[1]] = '\0';
}
