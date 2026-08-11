/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_all_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:01:31 by asebban           #+#    #+#             */
/*   Updated: 2025/05/15 14:25:37 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	toggle_quote(t_varctx *ctx)
{
	char	c;

	c = ctx->in[ctx->pos[0]];
	if (c == '\'' && !ctx->double_s)
	{
		ctx->single = !ctx->single;
		ctx->out[ctx->pos[1]++] = c;
		ctx->pos[0]++;
	}
	else if (c == '"' && !ctx->single)
	{
		ctx->double_s = !ctx->double_s;
		ctx->out[ctx->pos[1]++] = c;
		ctx->pos[0]++;
	}
}

static	void	write_char(t_varctx *ctx)
{
	ctx->out[ctx->pos[1]++] = ctx->in[ctx->pos[0]++];
}

static	void	handle_var(t_varctx *ctx)
{
	char	name[PATH_MAX];
	int		k;
	int		i;

	k = 0;
	i = ctx->pos[0] + 1;
	while ((ft_isalnum(ctx->in[i]) || ctx->in[i] == '_')
		&& k < PATH_MAX - 1)
	{
		name[k++] = ctx->in[i++];
	}
	name[k] = '\0';
	ctx->pos[0] = i;
	write_value(ctx, get_env_value(ctx->sh->env, name));
}

static	void	process_change_all_var(t_varctx *ctx)
{
	while (ctx->in[ctx->pos[0]])
	{
		if (ctx->in[ctx->pos[0]] == '\'' && !ctx->double_s)
		{
			toggle_quote(ctx);
			continue ;
		}
		if (ctx->in[ctx->pos[0]] == '"' && !ctx->single)
		{
			toggle_quote(ctx);
			continue ;
		}
		if (ctx->in[ctx->pos[0]] == '$' && !ctx->single
			&& (ft_isalnum(ctx->in[ctx->pos[0] + 1])
				|| ctx->in[ctx->pos[0] + 1] == '_'))
			handle_var(ctx);
		else
			write_char(ctx);
	}
	ctx->out[ctx->pos[1]] = '\0';
}

char	*change_all_var(const char *str, t_shell *sh)
{
	t_varctx	ctx;
	int			maxlen;

	if (!str || !sh)
		return (NULL);
	maxlen = calculate_max_len(str, sh) + 64;
	ctx.out = ft_malloc(maxlen, 1);
	if (!ctx.out)
		return (NULL);
	ctx.in = str;
	ctx.sh = sh;
	ctx.single = false;
	ctx.double_s = false;
	ctx.pos[0] = 0;
	ctx.pos[1] = 0;
	process_change_all_var(&ctx);
	return (ctx.out);
}
