CXX     = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I./include

NAME    = ircserver
BOT     = ircbot

SRCS    = src/main.cpp \
			src/server/Server.cpp \
			src/server/Client.cpp \
           	src/server/ServerInit.cpp \
		  	src/server/CommandHandler.cpp \
			src/server/Channel.cpp \
			src/server/JoinCommand.cpp \
			src/server/TopicCommand.cpp \
			src/server/KickCommand.cpp \
			src/server/PrivmsgCommand.cpp \
			src/server/NoticeCommand.cpp \
			src/server/InviteCommand.cpp \
			src/server/ModeCommand.cpp

BOT_SRCS = src/bot/Bot.cpp \
		   src/bot/main.cpp

HEADERS = include/Client.hpp \
          include/Server.hpp \
          include/Channel.hpp \
          include/Bot.hpp

OBJS    = $(SRCS:.cpp=.o)
BOT_OBJS = $(BOT_SRCS:.cpp=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(BOT): $(BOT_OBJS)
	$(CXX) $(CXXFLAGS) $(BOT_OBJS) -o $(BOT)

bonus: $(NAME) $(BOT)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOT_OBJS)

fclean: clean
	rm -f $(NAME) $(BOT)

re: fclean $(NAME)

.PHONY: clean
