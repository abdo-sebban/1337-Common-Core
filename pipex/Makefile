CC         = cc
CFLAGS     = -Wall -Wextra -Werror
RM         = rm -f
NAME       = pipex

MANDATORY  = mandatory
BONUS      = bonus
UTILS      = utiles
INCLUDES   = includes

MANDATORY_SRCS = $(MANDATORY)/pipex.c $(MANDATORY)/usage_pipex.c $(MANDATORY)/exit.c $(MANDATORY)/acces.c
BONUS_SRCS     = $(BONUS)/pipex_bonus.c $(BONUS)/get_next_line.c $(BONUS)/usage_pipex_bonus.c $(BONUS)/here_doc.c\
				 $(BONUS)/error.c $(BONUS)/ft_strncmp.c
UTILS_SRCS     = $(UTILS)/free_tab.c $(UTILS)/ft_count_word.c\
                 $(UTILS)/ft_putchar_fd.c $(UTILS)/ft_putendl_fd.c $(UTILS)/ft_putstr_fd.c\
                 $(UTILS)/ft_split.c $(UTILS)/ft_strcmp.c $(UTILS)/ft_strdup.c $(UTILS)/ft_allocation.c\
                 $(UTILS)/ft_strjoin.c $(UTILS)/ft_strlcat.c $(UTILS)/ft_strlcpy.c\
                 $(UTILS)/ft_strlen.c $(UTILS)/ft_substr.c $(UTILS)/get_path.c 

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o) $(UTILS_SRCS:.c=.o)
BONUS_OBJS     = $(BONUS_SRCS:.c=.o) $(UTILS_SRCS:.c=.o)

all: $(NAME) $(INCLUDES)/pipex.h

$(NAME): $(MANDATORY_OBJS) $(INCLUDES)/pipex.h
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) -o $(NAME)

bonus: .bonus

.bonus: $(BONUS_OBJS) $(INCLUDES)/pipex_bonus.h
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME)
	@touch .bonus

clean:
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) .bonus

re: fclean all

.PHONY: all bonus clean fclean re
