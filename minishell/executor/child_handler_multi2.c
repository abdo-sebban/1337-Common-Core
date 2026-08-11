/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handler_multi2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:50:00 by asebban           #+#    #+#             */
/*   Updated: 2025/05/08 16:25:19 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	**build_sh_args(char *cmd)
{
	char	**sh_args;

	sh_args = ft_malloc(sizeof(char *) * 4, 1);
	if (!sh_args)
		return (NULL);
	sh_args[0] = "/bin/sh";
	sh_args[1] = "-c";
	sh_args[2] = cmd;
	sh_args[3] = NULL;
	return (sh_args);
}

static	void	exec_fallback(char **args, char **envp)
{
	size_t	total_len;
	int		i;
	char	*cmd;
	int		j;
	char	**sh_args;

	1 && (j = 0, i = 0);
	total_len = 0;
	while (args[i])
		total_len += ft_strlen(args[i++]) + 1;
	cmd = ft_malloc(total_len + 1, 1);
	if (!cmd)
		(ft_malloc(0, 0), exit(1));
	cmd[0] = '\0';
	while (args[j])
	{
		ft_strcat(cmd, args[j]);
		if (args[j + 1])
			ft_strcat(cmd, " ");
		j++;
	}
	sh_args = build_sh_args(cmd);
	execve("/bin/sh", sh_args, envp);
	perror("fallback execve failed");
	(ft_malloc(0, 0), exit(127));
}

void	try_exec_with_fallback(char *path,
		char **args, char **envp, t_shell *shell)
{
	execve(path, args, envp);
	(void)shell;
	if (errno == ENOENT || errno == EACCES || errno == ENOEXEC)
		exec_fallback(args, envp);
	ft_malloc(0, 0);
	exit(126);
}
