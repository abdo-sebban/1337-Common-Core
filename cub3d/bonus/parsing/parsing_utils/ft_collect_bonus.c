/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:14:10 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:14:10 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	append_node(t_line_node **head, char *line)
{
	t_line_node	*new_node;
	t_line_node	*cur;

	new_node = malloc(sizeof(t_line_node));
	if (!new_node)
		return (false);
	new_node->line = line;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
	return (true);
}

bool	free_line_list(t_line_node *head)
{
	t_line_node	*cur;
	t_line_node	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		free(cur->line);
		free(cur);
		cur = next;
	}
	return (false);
}

bool	read_map_lines(int fd, t_line_node **head, char *first_line, int *count)
{
	char	*line;

	line = first_line;
	if (!append_node(head, line))
		return (false);
	(*count)++;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_is_empty(line))
		{
			free(line);
			ft_print_error("Error\nInvalid map\n");
			return (false);
		}
		if (!append_node(head, line))
			return (false);
		(*count)++;
	}
	return (true);
}

static bool	list_to_array(t_line_node *head, int count, char ***out_lines)
{
	char		**buffer;
	t_line_node	*cur;
	t_line_node	*next;
	int			i;

	buffer = malloc(sizeof(char *) * count);
	if (!buffer)
		return (free_line_list(head));
	cur = head;
	i = 0;
	while (i < count)
	{
		buffer[i] = cur->line;
		next = cur->next;
		free(cur);
		cur = next;
		i++;
	}
	*out_lines = buffer;
	return (true);
}

bool	ft_collect(int fd, char *first_line,
		char ***out_lines, int *num_lines)
{
	t_line_node	*head;
	int			count;

	head = NULL;
	count = 0;
	if (!first_line || !out_lines || !num_lines)
		return (false);
	if (!read_map_lines(fd, &head, first_line, &count))
		return (free_line_list(head));
	if (!list_to_array(head, count, out_lines))
		return (false);
	*num_lines = count;
	return (true);
}
