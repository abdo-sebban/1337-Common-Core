CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = Harl.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = Harl
HEADER = Harl.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADER)
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
