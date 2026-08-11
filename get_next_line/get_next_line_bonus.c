/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:19:59 by asebban           #+#    #+#             */
/*   Updated: 2024/11/22 20:10:51 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			charactere;

	charactere = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == charactere)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == charactere)
		return ((char *) &s[i]);
	return (NULL);
}

static char	*is_line(char *line)
{
	char	*rest;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (0);
	rest = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!rest || *rest == 0)
	{
		free(rest);
		rest = NULL;
	}
	line[i + 1] = 0;
	return (rest);
}

static char	*get_next_line_helper(int fd, char *rest, char *buffer)
{
	ssize_t	byte_read;
	char	*tmp;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(rest);
			return (0);
		}
		else if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
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

char	*get_next_line(int fd)
{
	static char	*rest[FD];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(buffer);
		if (fd < 0 || fd > FD)
			return (NULL);
		free(rest[fd]);
		rest[fd] = NULL;
		buffer = NULL;
		return (0);
	}
	line = get_next_line_helper(fd, rest[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rest[fd] = is_line(line);
	return (line);
}
