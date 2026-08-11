CC          = cc
CFLAGS      = -Wall -Werror -Wextra

NAME        = push_swap
BONUS_NAME  = checker

SRC_DIR      = srcs
OBJ_DIR      = obj
BONUS_SRC_DIR = bonus
BONUS_OBJ_DIR = bonus_obj
INC_DIR      = includes

SRC          = srcs/Error.c \
               srcs/Free_stack.c \
               srcs/abs.c \
               srcs/assign_index.c \
               srcs/fill_stack_values.c \
               srcs/first_value.c \
               srcs/ft_atoi.c \
               srcs/ft_get_stack_size.c \
               srcs/ft_handl_av.c \
               srcs/ft_move.c \
               srcs/ft_putstr.c \
               srcs/ft_split.c \
               srcs/ft_strdup.c \
               srcs/ft_strjoin.c \
               srcs/ft_strlcat.c \
               srcs/ft_strlcpy.c \
               srcs/ft_strlen.c \
               srcs/ft_strlen_stack.c \
               srcs/get_cost.c \
               srcs/is_correct_input.c \
               srcs/is_digit.c \
               srcs/is_empty.c \
               srcs/is_sign.c \
               srcs/mbstr_cmp.c \
               srcs/position.c \
               srcs/push.c \
               srcs/push_swap.c \
               srcs/reverse_rotate.c \
               srcs/rotate.c \
               srcs/sort.c \
               srcs/sort_tiny.c \
               srcs/stack_add_bottom.c \
               srcs/swap.c \

OBJ          = obj/Error.o \
               obj/Free_stack.o \
               obj/abs.o \
               obj/assign_index.o \
               obj/fill_stack_values.o \
               obj/first_value.o \
               obj/ft_atoi.o \
               obj/ft_get_stack_size.o \
               obj/ft_handl_av.o \
               obj/ft_move.o \
               obj/ft_putstr.o \
               obj/ft_split.o \
               obj/ft_strdup.o \
               obj/ft_strjoin.o \
               obj/ft_strlcat.o \
               obj/ft_strlcpy.o \
               obj/ft_strlen.o \
               obj/ft_strlen_stack.o \
               obj/get_cost.o \
               obj/is_correct_input.o \
               obj/is_digit.o \
               obj/is_empty.o \
               obj/is_sign.o \
               obj/mbstr_cmp.o \
               obj/position.o \
               obj/push.o \
               obj/push_swap.o \
               obj/reverse_rotate.o \
               obj/rotate.o \
               obj/sort.o \
               obj/sort_tiny.o \
               obj/stack_add_bottom.o \
               obj/swap.o \

BONUS_SRC    = bonus/Error.c \
               bonus/Free_stack.c \
               bonus/assign_index.c \
               bonus/checker.c \
               bonus/fill_stack_values.c \
               bonus/first_value.c \
               bonus/ft_atoi.c \
               bonus/ft_get_stack_size.c \
               bonus/ft_handl_av.c \
               bonus/ft_putstr.c \
               bonus/ft_split.c \
               bonus/ft_strcmp.c \
               bonus/ft_strlen_stack.c \
               bonus/get_next_line.c \
               bonus/get_next_line_utils.c \
               bonus/is_correct_input.c \
               bonus/is_digit.c \
               bonus/is_empty.c \
               bonus/is_sign.c \
               bonus/mbstr_cmp.c \
               bonus/push.c \
               bonus/reverse_rotate.c \
               bonus/rotate.c \
               bonus/stack_add_bottom.c \
               bonus/swap.c

BONUS_OBJ    = bonus_obj/Error.o \
               bonus_obj/Free_stack.o \
               bonus_obj/assign_index.o \
               bonus_obj/checker.o \
               bonus_obj/fill_stack_values.o \
               bonus_obj/first_value.o \
               bonus_obj/ft_atoi.o \
               bonus_obj/ft_get_stack_size.o \
               bonus_obj/ft_handl_av.o \
               bonus_obj/ft_putstr.o \
               bonus_obj/ft_split.o \
               bonus_obj/ft_strcmp.o \
               bonus_obj/ft_strlen_stack.o \
               bonus_obj/get_next_line.o \
               bonus_obj/get_next_line_utils.o \
               bonus_obj/is_correct_input.o \
               bonus_obj/is_digit.o \
               bonus_obj/is_empty.o \
               bonus_obj/is_sign.o \
               bonus_obj/mbstr_cmp.o \
               bonus_obj/push.o \
               bonus_obj/reverse_rotate.o \
               bonus_obj/rotate.o \
               bonus_obj/stack_add_bottom.o \
               bonus_obj/swap.o

all: $(NAME)

$(NAME): $(OBJ) $(INC_DIR)/push_swap.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(INC_DIR)/push_swap_bonus.h
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

obj/%.o: srcs/%.c $(INC_DIR)/push_swap.h | obj
	$(CC) $(CFLAGS) -c $< -o $@

bonus_obj/%.o: bonus/%.c $(INC_DIR)/push_swap_bonus.h | bonus_obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

bonus_obj:
	mkdir -p bonus_obj

clean:
	rm -rf obj bonus_obj

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: clean