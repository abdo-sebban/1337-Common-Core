/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grb_coll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:00:22 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/20 12:42:48 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*err(int c)
{
	(void)c;
	perror ("minishell\n");
	return (NULL);
}

void	close_all_fds(void)
{
	long	max_fd;
	long	i;

	i = 3;
	max_fd = 1024;
	while (i < max_fd)
	{
		close((int)i);
		i++;
	}
}

void	free_all(t_collect **head)
{
	t_collect	*current;
	t_collect	*next;

	if (!*head || !head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	*head = NULL;
	rl_clear_history();
}

void	*ft_malloc(size_t size, int mode)
{
	static t_collect	*head;
	void				*data;
	t_collect			*node;

	data = NULL;
	node = NULL;
	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (err(25));
		node = malloc(sizeof(t_collect));
		if (!node)
			return (free(data), err(25));
		node->data = data;
		node->next = head;
		head = node;
	}
	else if (mode == 0)
	{
		free_all(&head);
		close_all_fds();
		head = NULL;
	}
	return (data);
}

bool	check_tty(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_malloc(0, 0);
		return (false);
	}
	return (true);
}
