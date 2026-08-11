/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:07:22 by selbouka          #+#    #+#             */
/*   Updated: 2025/04/17 20:07:22 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <linux/limits.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define FAILED 102
# define OK 100
# define EXIT_GET 0
# define EXIT_SET 1

# define FAIL_SYSCALL       -1
# define OKAY               0
# define FAIL_SYSCALL_PARENT    1
# define FAIL_SYSCALL_CHILD  1

# define FAIL -1
# define PARENT 1
# define CHILD  3
# define ERR "cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n"

typedef struct s_shell
{
	char					*rl_input;
	char					*rl_copy;
	struct s_environ_list	*env;
	struct s_lexer_list		*lex_head;
	struct s_executor		*executor;
}	t_shell;

typedef struct s_environ_list
{
	struct s_environ_node	*head;
	int						size;
}	t_environ_list;

typedef struct s_environ_node
{
	char					*key;
	char					*value;
	struct s_environ_node	*next;
}	t_environ_node;

typedef enum s_token
{
	EMPTY = 0,
	CMD = 1,
	REDERECT_IN = 2,
	rederect_out = 3,
	APPEND = 4,
	HEREDOC = 5,
	PIPE	= 6,
}	t_token;

typedef struct s_split
{
	char			*str;
	int				is_operator;
	struct s_split	*next;
}	t_split;

typedef struct s_lexer_list
{
	char				*str;
	t_token				type;
	struct s_lexer_list	*prev;
	struct s_lexer_list	*next;
}	t_lexer_list;

typedef struct s_executor
{
	int					id;
	int					size;
	int					fd_in;
	int					fd_out;
	bool				rederect_out;
	bool				append;
	bool				redirect_input;
	bool				heredoc;
	char				**path;
	char				**execs;
	bool				flag;
	struct s_executor	*prev;
	struct s_executor	*next;
}	t_executor;

typedef struct s_info
{
	int		wstatus;
	t_shell	*shell;
	int		stdin_copy;
	pid_t	*pids;
}	t_info;

typedef struct garbage_c
{
	void				*data;
	struct garbage_c	*next;
}	t_collect;

typedef struct s_varctx
{
	const char	*in;
	char		*out;
	int			max;
	size_t		pos[2];
	bool		single;
	bool		double_s;
	t_shell		*sh;
}	t_varctx;

typedef struct s_export_data
{
	char	*key;
	char	*value;
	bool	append;
}	t_export_data;

typedef struct s_replinfo
{
	size_t	i;
	size_t	o;
}	t_replinfo;

int				ft_special(char x, int her);
int				skip(char	**input, int j);
void			ft_cat(char *str);
char			*get_next_token(const char *s, int *index, int *is_op);
char			*parse_token(const char *s, int *i);
int				parse_literal(const char *s, int *i, char **res);
int				parse_quoted(const char *s, int *i, char **res);
char			*append_segment(char *res, const char *seg, int len);
int				count_tokens(const char *s);
int				advance_token(const char *s, int idx);
int				ft_operator_len(const char *s);
char			*ft_dup_token(const char *str, int len);
int				skip_spaces(const char *s, int i);
char			*build_full_str(const t_environ_node *node);
void			print_sorted_env(t_environ_list *env);
void			print_sorted_nodes(const t_environ_node *sorted);
t_environ_node	*create_sorted_copy(const t_environ_list *env_list);
void			insert_sorted(t_environ_node **sorted, \
t_environ_node *new_node);
t_export_data	parse_export_str(const char *str);
void			update_node(t_environ_node *node, t_export_data *data);
void			add_new_node(t_shell *shell, t_export_data *data);
void			exporting(t_shell *shell, char *str);
int				export_args(t_shell *shell, char **args);
void			handle_no_file_error(void);
void			replace_soh_with_dollar_in_env(t_environ_list *env_list);
void			replace_soh_with_dollar(char *str);
char			*ft_replace_var3(const char *seg, t_shell *shell, int flag);
void			append_var(const char *seg, t_shell *shell, \
char *result, int ptrs[3]);
void			close_all_fds(void);
void			fill_replaced_segment(const char *seg, \
t_shell *shell, char *result, int flag);
char			*save_pwd(int action, char *value);
int				unset(t_shell *shell, char **args);
int				echo(char **args);
int				handle_single_builtin(t_shell *shell);
bool			is_builtin(char *exec);
int				pwd(t_environ_list *env);
int				cd(t_shell *shell, char **arg);
void			*ft_malloc(size_t size, int mode);
int				exit_builtin(t_shell *shell, char **args, int in_pipe);
int				env(t_shell *shell, char **args);
int				export(t_shell *shell, char **args);
int				exit_status(int action, int value);
t_environ_node	*ft_getenv(t_environ_list *env, char *key);
bool			is_valid_identifier(char *str);
int				export_no_args(t_shell *shell);
void			print_sorted_env(t_environ_list *env);
int				check_syntax(char *input);
void			clean_exit(t_shell *shell, int exit_code);
int				count_args(char **args);
void			print_exit_if_needed(int in_pipe);
void			handle_no_args(t_shell *shell, int exit_code, \
int arg_count, int in_pipe);
int				handle_non_numeric(char *arg, t_shell *shell, int in_pipe);
int				handle_too_many(int arg_count, int in_pipe);
void			wait_pipeline(t_info *info, int number);
t_environ_node	*create_environ_node(char *var);
t_environ_node	*add_back_environ_node(t_environ_list *env,
					t_environ_node *node);
t_environ_list	*init_environ(char **envp);
t_environ_list	*empty_environ(t_environ_list *env);
t_shell			*init_shell(char **env);
t_executor		*prepare_executor(t_shell *shell);
t_executor		*fill_executor_list(t_shell *shell, t_executor *list);
void			set_path_executor(t_executor *list, t_environ_list *env);
t_environ_node	*get_node(t_environ_list *env, char *key);
t_info			*init_info(t_shell *shell);
int				child_handler_multi(int *fildes,
					t_executor *current, t_info *info);
void			handle_multi(t_info *info, t_executor *current);
t_info			*init_info(t_shell *shell);
int				check_pipe(char *input);
char			**transform_environ_array(t_shell *shell);
char			*get_path(t_shell *shell, bool printerror);
void			handle_single_child(t_shell *shell);
void			executor(t_shell *shell);
bool			handle_redirections_single_child(t_shell *shell);
char			*get_env_value(t_environ_list *env_list, char *key);
t_environ_node	*ft_getenv(t_environ_list *env, char *key);
int				is_cmdline_empty(const char *cmdline);
void			try_exec_with_fallback(char *path,
					char **args, char **envp, t_shell *shell);
char			*execute_other_helper(t_executor *current);
void			err_for_norm(void);
void			get_path_error(void);
char			*replace_vars1(const char *input, t_shell *shell);
char			*export_hard(char *str, t_shell *shell);
void			write_value(t_varctx *ctx, const char *val);
char			**ft_split1(char const *s, char c);
char			*process_line_expand_first_var(char *line, \
t_shell *shell);
char			*ft_replace_var3(const char *seg, \
t_shell *shell, int flag);
t_lexer_list	*tokenize(t_shell *shell);
t_lexer_list	*lexer(t_shell *shell);
char			*clean_rl_copy(char *rl_copy);
int				check_quote_syntax(const char *input);
bool			parser(t_shell *shell);
t_split			*ft_newsplit(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
void			signal_setup(int mode);
int				check_redirect_out(char *input, int j);
int				check_redirect_in(char *input, int j);
void			int_to_str(int num, char *str);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
t_token			which_type(char *s, int inside);
int				herdoc_status(int action, int value);
char			*handle_dollar_quotes(char *input);
char			*replace_var_equals_var(char *input, t_shell *shell);
int				all_value(char *seg, t_shell *shell);
char			*change_all_var(const char *str, t_shell *sh);
int				calculate_max_len(const char *str, t_shell *shell);
char			*process_tokens(char **tokens, t_shell *shell);
int				var_name_len1(const char *seg, int pos);
int				create_heredoc(char *delimiter, t_shell *shell);
int				is_last_delim_quoted(const char *cmdline);
char			*replace_vars_heredoc(char *input, t_shell *shell);
t_executor		*process_lexemes(t_executor *list, \
t_executor *current, t_lexer_list **lexer, t_shell *shell);
int				process_command(t_executor *current, t_lexer_list *lexer);
int				process_in_heredoc(t_executor *cur, \
t_lexer_list *lex, t_shell *sh);
int				process_out_append(t_executor *current, t_lexer_list *lexer);
bool			open_outputfile(t_executor *current, t_lexer_list *lexer);
bool			is_delimiter(const char *line, const char *delimiter);
void			handle_eof(void);
int				open_heredoc_pipe(int pipefd[2]);
size_t			buf_append(char *out, size_t o, const char *str);
size_t			append_exit_status(char *out, size_t o);
void			append_env_var(char *out, \
const char *start, t_shell *shell, size_t info[2]);
void			handle_variable_name(const char *input, \
size_t *idx, t_shell *shell, size_t *out_len);
void			calc_var_length(const char *input, \
size_t *idx, t_shell *shell, size_t *out_len);
size_t			handle_alpha_case(const char *input, \
char *out, t_replinfo *info, t_shell *shell);
void			lookup_and_append(const char *name_buf, \
char *out, t_replinfo *info, t_shell *shell);
size_t			extract_var_name(const char *input, \
t_replinfo *info, char *name_buf);
t_token			which_type(char *s, int inside);
int				find_token_pos(const char *rl, const char *s, int last_pos);
t_lexer_list	*create_lexer_list(char **input_array);
t_lexer_list	*allocate_lexer_nodes(int size);
int				count_input_array(char **input_array);
void			process_variable(const char *segment, \
char **res, int *i, t_shell *shell);
int				handle_expand_variable(const char *in, \
char **res, int *i, t_shell *shell);
char			*segment_expand(const char *segment, t_shell *shell);
char			*process_export_segment(const char *seg, t_shell *shell);
char			*expand_variables(const char *input, t_shell *shell);
int				handle_skip_heredoc(const char *in, char **res, int *i);
int				should_toggle_squote(char c, int skip_word);
void			append_char(char **res, const char *src, int len);
void			process_skip_word(const char *segment, \
char **res, int *i, int *skip_word);
char			*get_env_value2(const char *key, t_shell *shell);
char			*ft_strtrim1(const char *s1);
int				is_cmdline_empty(const char *cmdline);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
size_t			parse_var_name(const char *str, char **out_var);
char			*expand_present_var(const char *trimmed, t_shell *shell);
char			*expand_absent_var(const char *trimmed, \
size_t var_len, t_shell *shell);
char			*expand_vars_in(const char *src, t_shell *shell);
char			*process_single_chunk(char *chunk, t_shell *shell);
void			append_chunk(char **dst, \
size_t *dst_len, const char *src, size_t len);
size_t			process_double_redirect(char **out, size_t *out_len, int flag);
size_t			process_single_operator(char **out, \
size_t *out_len, char sym);
size_t			process_regular_char(char **out, \
size_t *out_len, const char *in);
void			app_result(char **pres);
const char		*skip_leading_spaces(const char *s);
void			minishell_loop(t_shell *shell);
bool			check_tty(void);
int				skip_quates(char **input);
int				check_fornorm(char **input);
int				count_herdoc(int action);
void			cleanup_redirections(t_executor *cur);
int				err_red(t_executor *cur);

#endif