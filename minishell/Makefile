CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
LIBFT = libft/libft.a

SRCM = main.c \
		executor/child_handler_multi.c   executor/child_handler_multi2.c  executor/executor.c  executor/handle_multi.c  executor/handle_single_child.c  executor/single_child_util_2.c  executor/single_child_utils.c \
		parsing/fill_executor_list.c  parsing/handle_signals.c  parsing/parser.c  parsing/prep_executor.c  parsing/syntax_cheker.c  parsing/tokenize.c \
		utils/clean_rl_copy.c  utils/environ_list_utils.c  utils/ft_newsplit.c  utils/ft_strcmp.c  utils/ft_strcpy.c  utils/grb_coll.c  utils/init_shell.c  utils/set_path_executor.c \
		builtins_fun/ft_cd.c  builtins_fun/ft_pwd.c  builtins_fun/handle_single_builtin.c builtins_fun/env_builtin.c builtins_fun/echo_builtin.c utils/ft_get_value.c utils/exit_status.c builtins_fun/export_builtin.c builtins_fun/utils.c \
		builtins_fun/unset_builtin.c builtins_fun/exit_builtin.c builtins_fun/builtins_utils.c builtins_fun/handle_single_builtin2.c utils/handle_dollar_quotes.c utils/replace_var_equals_var.c utils/all_values.c \
		executor/path_handler_multi.c  utils/replace_vars.c  utils/export_hard.c utils/change_all_var.c utils/calculate_len.c utils/ft_split_utils2.c utils/ft_split_utils1.c utils/replace_var_utils.c builtins_fun/export_utils2.c builtins_fun/export_utils1.c \
		utils/expand_hard2.c parsing/herdoc_handler.c parsing/process_lexemes.c parsing/process.c parsing/last_del.c parsing/herdoc_var.c parsing/herdoc_utils.c parsing/herdoc_var_utils.c parsing/herdoc_val_utils.c parsing/token_utils.c utils/replace_vars_1.c  utils/replace_vars_2.c utils/ft_realloc.c utils/expand_utils.c utils/expand_utils2.c utils/minishell_loop.c utils/replace_soh.c utils/replace_var3.c \
		builtins_fun/exit_utils2.c builtins_fun/exit_utils.c parsing/allocate_lexer_nodes.c utils/fill_replaced_segment.c utils/count.c parsing/cleanup_redirections.c

SRCLIB = libft/ft_atoi.c    libft/ft_isalnum.c  libft/ft_isdigit.c   libft/ft_memchr.c  libft/ft_memmove.c     libft/ft_putendl_fd.c  libft/ft_split1.c  libft/ft_strchr.c    libft/ft_strjoin2.c  libft/ft_strlcpy.c  libft/ft_strncat.c  libft/ft_strrchr.c  libft/ft_tolower.c \
		 libft/ft_bzero.c   libft/ft_isalpha.c  libft/ft_isprint.c  libft/ft_memcmp.c  libft/ft_memset.c      libft/ft_putnbr_fd.c   libft/ft_split.c   libft/ft_strdup.c    libft/ft_strjoin.c   libft/ft_strlen.c   libft/ft_strncmp.c  libft/ft_strtrim.c  libft/ft_toupper.c  libft/new_split.c \
		 libft/ft_calloc.c  libft/ft_isascii.c  libft/ft_itoa.c   libft/ft_memcpy.c  libft/ft_putchar_fd.c  libft/ft_putstr_fd.c   libft/ft_strcat.c  libft/ft_striteri.c  libft/ft_strlcat.c   libft/ft_strmapi.c  libft/ft_strnstr.c  libft/ft_substr.c

OBJS = $(SRCM:.c=.o)

MAKEFLAGS += --no-print-directory
CYAN = \033[1;36m
RESET = \033[0m 

all: $(LIBFT) $(NAME)
	@echo "$(CYAN) __  __  __  _  _  __  ___  _  _  ___  __    __   $(RESET)"
	@echo "$(CYAN)(  \/  )(  )( \( )(  )/ __)( )( )(  _)(  )  (  )  $(RESET)"
	@echo "$(CYAN) )    (  )(  )  (  )( \__ \ )__(  ) _) )(__  )(__ $(RESET)"
	@echo "$(CYAN)(_/\_\/)(__)(_)\_)(__)(___/(_)(_)(___)(____)(____)$(RESET)"
	@echo ""

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c includes/minishell.h  libft/libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): libft/libft.h $(SRCLIB)
	@make -C libft/

clean:
	@echo "Cleaning up… 🧹 🧼 🧽 ✨"
	@rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY : clean
