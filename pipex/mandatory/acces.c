/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:50:53 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 10:47:51 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	access_infile(char *infile, int *p_fd)
{
	if (access(infile, F_OK) == -1)
	{
		perror("\033[31mError");
		close(p_fd[0]);
		close(p_fd[1]);
		exit(1);
	}
	if (access(infile, R_OK) == -1)
	{
		perror("\033[31mError");
		close(p_fd[0]);
		close(p_fd[1]);
		exit(1);
	}
}

void	access_outfile(char *outfile, int *p_fd)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("\033[31mError:");
		close(p_fd[0]);
		close(p_fd[1]);
		exit(1);
	}
	close(fd);
}
