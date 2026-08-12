/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:16:50 by asebban           #+#    #+#             */
/*   Updated: 2025/06/26 22:16:50 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line_helper(int fd, char *rest, char *buffer)
{
	ssize_t	byte__read;
	char	*tmp;

	byte__read = 1;
	while (byte__read > 0)
	{
		byte__read = read(fd, buffer, BUFFER_SIZE);
		if (byte__read == -1)
		{
			free(rest);
			return (NULL);
		}
		else if (byte__read == 0)
			break ;
		buffer[byte__read] = 0;
		if (!rest)
			rest = ft_strdup("");
		tmp = rest;
		rest = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rest);
}

char	*is_line(char *line)
{
	char	*rest;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0)
		return (NULL);
	rest = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!rest || *rest == 0)
	{
		free(rest);
		rest = NULL;
	}
	line[i + 1] = 0;
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*line;

	buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(rest);
		free(buffer);
		rest = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = get_next_line_helper(fd, rest, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rest = is_line(line);
	return (line);
}
