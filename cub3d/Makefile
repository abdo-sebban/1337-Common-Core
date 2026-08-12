NAME = cub3d
BONUS_NAME = cub3d_bonus
CC = cc 
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR)
BONUS_CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(BONUS_LIBFT_DIR)
LDFLAGS = -lmlx -framework OpenGL -framework AppKit
LIBFT_DIR = mandatory/libft
LIBFT_LIB = mandatory/libft/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h
BONUS_LIBFT_DIR = bonus/libft
BONUS_LIBFT_LIB = bonus/libft/libft.a
BONUS_LIBFT_HEADER = $(BONUS_LIBFT_DIR)/libft.h
HEADER = mandatory/includes/cub3d.h
BONUS_HEADER = bonus/includes/cub3d.h
ALL_HEADERS = $(HEADER) $(LIBFT_HEADER)
BONUS_ALL_HEADERS = $(BONUS_HEADER) $(BONUS_LIBFT_HEADER)
SRC = mandatory/parsing/parsing_utils/ft_alloc_matrix.c \
		mandatory/parsing/parsing_utils/ft_check_xpm.c \
		mandatory/parsing/parsing_utils/ft_collect.c \
		mandatory/parsing/parsing_utils/ft_print_error.c \
		mandatory/parsing/parsing_utils/ft_parse_header.c \
		mandatory/parsing/parsing_utils/ft_parse_map.c \
		mandatory/parsing/parsing_utils/ft_set_colors.c \
		mandatory/parsing/parsing_utils/ft_set_texture_path.c \
		mandatory/parsing/parsing_utils/ft_split_rgb.c \
		mandatory/parsing/parsing_utils/ft_check_validation.c \
		mandatory/parsing/ft_parsing.c \
		mandatory/raycaster/init_game.c \
		mandatory/raycaster/init_game_utils.c \
		mandatory/raycaster/game_loop.c \
		mandatory/raycaster/cleanup_game.c \
		mandatory/raycaster/input_handling.c \
		mandatory/raycaster/input_handling_utils.c \
		mandatory/raycaster/raycaster.c \
		mandatory/raycaster/init_pos.c \
		mandatory/raycaster/dda.c \
		mandatory/raycaster/calc_wall.c \
		mandatory/src/main.c \
		mandatory/parsing/parsing_utils/ft_check_leaks.c \
		mandatory/parsing/parsing_utils/ft_scan_map.c
BONUS_SRC = bonus/parsing/parsing_utils/ft_alloc_matrix_bonus.c \
		bonus/parsing/parsing_utils/ft_check_xpm_bonus.c \
		bonus/parsing/parsing_utils/ft_collect_bonus.c \
		bonus/parsing/parsing_utils/ft_print_error_bonus.c \
		bonus/parsing/parsing_utils/ft_parse_header_bonus.c \
		bonus/parsing/parsing_utils/ft_parse_map_bonus.c \
		bonus/parsing/parsing_utils/ft_set_colors_bonus.c \
		bonus/parsing/parsing_utils/ft_set_texture_path_bonus.c \
		bonus/parsing/parsing_utils/ft_split_rgb_bonus.c \
		bonus/parsing/parsing_utils/ft_check_validation_bonus.c \
		bonus/parsing/ft_parsing_bonus.c \
		bonus/raycaster/init_game_bonus.c \
		bonus/raycaster/init_game_utils_bonus.c \
		bonus/raycaster/game_loop_bonus.c \
		bonus/raycaster/cleanup_game_bonus.c \
		bonus/raycaster/input_handling_bonus.c \
		bonus/raycaster/input_handling_utils_bonus.c \
		bonus/raycaster/raycaster_bonus.c \
		bonus/raycaster/init_pos_bonus.c \
		bonus/raycaster/dda_bonus.c \
		bonus/raycaster/calc_wall_bonus.c \
		bonus/src/main_bonus.c \
		bonus/raycaster/mini_map_bonus.c \
		bonus/raycaster/check_doors_bonus.c \
		bonus/parsing/parsing_utils/ft_check_leaks_bonus.c \
		bonus/parsing/parsing_utils/ft_scan_map_bonus.c
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
all: $(LIBFT_LIB) $(NAME)
bonus: $(BONUS_LIBFT_LIB) $(BONUS_NAME)
$(LIBFT_LIB): force_libft
	make -C $(LIBFT_DIR)
$(BONUS_LIBFT_LIB): force_libft
	make -C $(BONUS_LIBFT_DIR)
force_libft:
	@true
$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)
$(BONUS_NAME): $(BONUS_OBJ) $(BONUS_LIBFT_LIB)
	$(CC) $(BONUS_OBJ) $(BONUS_LIBFT_LIB) $(LDFLAGS) -o $(BONUS_NAME)
mandatory/%.o: mandatory/%.c $(ALL_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
bonus/%.o: bonus/%.c $(BONUS_ALL_HEADERS)
	$(CC) $(BONUS_CFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ) $(BONUS_OBJ)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(BONUS_LIBFT_DIR)
fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(BONUS_LIBFT_DIR)
re: fclean all
.PHONY: clean force_libft