# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asebban <asebban@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/24 13:05:02 by asebban           #+#    #+#              #
#    Updated: 2024/11/28 09:42:21 by asebban          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = printf.a

AR	= ar rc

SRC	= ft_print_low_hex.c ft_putnbr.c ft_print_up_hex.c \
		ft_put_uns_nbr.c ft_putstr.c ft_print_hex.c ft_printf.c \
		ft_putchar.c
			 
OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $?

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : clean