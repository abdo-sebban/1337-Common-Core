NAME 		= fixed
CXX  		= c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
SRC         = main.cpp Fixed.cpp
OBJ         = $(SRC:.cpp=.o)
Header		= Fixed.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(Header)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
