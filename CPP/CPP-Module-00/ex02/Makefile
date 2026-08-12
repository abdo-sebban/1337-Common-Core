NAME    = account
CPP     = c++
CPPFLAGS= -Wall -Wextra -Werror -std=c++98

SRCS    = Account.cpp tests.cpp
OBJS    = $(SRCS:.cpp=.o)
HEADERS = Account.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
