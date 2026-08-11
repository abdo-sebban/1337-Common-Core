/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:32:54 by asebban           #+#    #+#             */
/*   Updated: 2025/02/09 11:47:14 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>

typedef struct t_quote
{
	int		in_quote;
	char	quote_type;
}	t_quote;

char	*get_next_line(int fd);
void	error(void);
char	*get_path(char *cmd, char **env);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_free_tab(char **tab);
void	usage_pipex_bonus(void);
int		open_file(char *argv, int i);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	here_doc(char *limiter, int argc);
int		ft_count_word(char *str, char c);
char	*ft_allocation(char *str, char set);
int		ft_str_len_sep(char *str, char set);
char	*validate_and_get_path(char **command, char **envp);

#endif