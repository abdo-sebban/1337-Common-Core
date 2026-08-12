CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = BraiiiiiiinnnzzzZ
SRC     = newZombie.cpp randomChump.cpp Zombie.cpp main.cpp
OBJ     = $(SRC:.cpp=.o)
HEADER  = Zombie.hpp


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
