NAME = Identify

CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Base.cpp  generate.cpp  identifyBypointer.cpp  identifyByReference.cpp

OBJ = $(SRC:.cpp=.o)

HEADER = A.hpp Base.hpp  B.hpp  C.hpp  functions.hpp 

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:  clean 
