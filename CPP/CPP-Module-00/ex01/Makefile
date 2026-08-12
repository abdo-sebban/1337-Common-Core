NAME        = phonebook
CPP         = c++
CPPFLAGS    = -Wall -Wextra -Werror -std=c++98
HEADERS     = Contact.hpp PhoneBook.hpp

SRCS        = main.cpp Contact.cpp PhoneBook.cpp
OBJS        = $(SRCS:.cpp=.o)

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
