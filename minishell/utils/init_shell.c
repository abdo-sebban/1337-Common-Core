/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:42:18 by asebban           #+#    #+#             */
/*   Updated: 2025/05/14 13:26:29 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_environ_list	*empty_environ(t_environ_list *env)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	char	*shlvl;
	char	*path;
	char	*mini;

	if (!getcwd(cwd, PATH_MAX))
		return (perror("minishell: getcwd"), NULL);
	pwd = ft_strjoin("PWD=", cwd);
	shlvl = ft_strdup("SHLVL=1");
	path = ft_strdup(\
	"PATH=/usr/local/sbin:"\
	"/usr/local/bin:/usr/sbin:"\
	"/usr/bin:/sbin:/bin");
	mini = ft_strdup("_=/home/asebban/Desktop/"\
	"shell_with_selbouka/./minishell");
	if (!pwd || !shlvl || !path || !mini
		|| !add_back_environ_node(env, create_environ_node(pwd))
		|| !add_back_environ_node(env, create_environ_node(shlvl))
		|| !add_back_environ_node(env, create_environ_node(mini))
		|| !add_back_environ_node(env, create_environ_node(path)))
		return (NULL);
	return (env);
}

t_environ_list	*init_environ(char **envp)
{
	t_environ_list	*env;
	t_environ_node	*node;
	char			*env_var;

	env = (t_environ_list *)ft_malloc(sizeof(t_environ_list), 1);
	if (!env)
		return (NULL);
	env->head = NULL;
	if (!*envp)
		return (empty_environ(env));
	while (*envp)
	{
		env_var = ft_strdup(*envp);
		if (!env_var)
			return (NULL);
		node = create_environ_node(env_var);
		if (!node)
			return (NULL);
		add_back_environ_node(env, node);
		envp++;
	}
	return (env);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = (t_shell *)ft_malloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->env = init_environ(env);
	if (!shell->env)
		return (NULL);
	shell->lex_head = NULL;
	shell->executor = NULL;
	return (shell);
}
