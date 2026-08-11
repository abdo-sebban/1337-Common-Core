/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:50:49 by asebban           #+#    #+#             */
/*   Updated: 2025/05/16 14:34:36 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	is_n_option(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	total_len(char **args)
{
	int	len;

	len = 0;
	while (*args)
	{
		len += ft_strlen(*args) + 1;
		args++;
	}
	return (len);
}

void	full_buff(char **arg, int k, char *buff, int *j)
{
	int	i;

	i = 0;
	while (arg[k][i])
	{
		buff[*j] = arg[k][i];
		i++;
		(*j)++;
	}
	if (arg[k + 1])
	{
		buff[*j] = ' ';
		(*j)++;
	}
}

int	echo(char **args)
{
	int			i;
	int			newline;
	char		*buff;
	size_t		len;
	int			j;

	1 && (j = 0, len = total_len(args));
	buff = ft_malloc (len + 1, 1);
	if (!buff)
		return (0);
	i = 1;
	newline = 1;
	while (args[i] && is_n_option(args[i]))
		1 && (newline = 0, i++);
	while (args[i])
	{
		full_buff(args, i, buff, &j);
		i++;
	}
	buff[j] = '\0';
	if (newline)
		printf ("%s\n", buff);
	else
		write(1, buff, ft_strlen(buff));
	return (ft_bzero(buff, ft_strlen (buff)), EXIT_SUCCESS);
}
