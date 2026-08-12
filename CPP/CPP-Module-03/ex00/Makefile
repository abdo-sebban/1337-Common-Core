CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = ClapTrap
SRC     = ClapTrap.cpp main.cpp
OBJ     = $(SRC:.cpp=.o)
HEADER  = ClapTrap.hpp

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean