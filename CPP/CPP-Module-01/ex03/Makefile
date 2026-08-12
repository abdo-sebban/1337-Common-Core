CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = Weapon
SRC     = main.cpp Weapon.cpp HumanA.cpp HumanB.cpp
OBJ     = $(SRC:.cpp=.o)
HEADER  = HumanA.hpp HumanB.hpp


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
