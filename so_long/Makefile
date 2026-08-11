NAME			= so_long
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
MLX_FLAGS		= -lmlx -framework OpenGL -framework AppKit

UTILS_DIR		= utils
GNL_DIR			= get_next_line
PRINTF_DIR		= ft_printf

UTILS_SRC		= $(UTILS_DIR)/check_extension.c\
					$(UTILS_DIR)/mov_player.c\
					$(UTILS_DIR)/pars_map4_utils.c\
					$(UTILS_DIR)/setup_game.c\
					$(UTILS_DIR)/ft_strcmp.c\
					$(UTILS_DIR)/pars_map2_utils.c\
					$(UTILS_DIR)/pars_map5_utils.c\
					$(UTILS_DIR)/setup_hooks.c\
					$(UTILS_DIR)/ft_strlcpy.c\
					$(UTILS_DIR)/pars_map3_utils.c\
					$(UTILS_DIR)/pars_map_utils.c\
					$(UTILS_DIR)/image_free.c

GNL_SRC			= $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
PRINTF_SRC		= $(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_print_hex.c $(PRINTF_DIR)/ft_print_low_hex.c $(PRINTF_DIR)/ft_print_up_hex.c $(PRINTF_DIR)/ft_put_uns_nbr.c $(PRINTF_DIR)/ft_putchar.c $(PRINTF_DIR)/ft_putnbr.c $(PRINTF_DIR)/ft_putstr.c

MAIN_SRC		= so_long.c

SRC				= $(MAIN_SRC) $(UTILS_SRC) $(GNL_SRC) $(PRINTF_SRC)
OBJ				= $(SRC:.c=.o)

INC				= includes/so_long.h $(GNL_DIR)/get_next_line.h $(PRINTF_DIR)/ft_printf.h

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re