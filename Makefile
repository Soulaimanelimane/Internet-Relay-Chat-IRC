SRC = ParseSide/utils_parse/ft_split.cpp ParseSide/errorside.cpp  ParseSide/mode_cmd.cpp ParseSide/join_cmd.cpp ParseSide/nick_cmd.cpp \
		ParseSide/pass_cmd.cpp ParseSide/privmsg_cmd.cpp ParseSide/invite_cmd.cpp ParseSide/user_cmd.cpp \
		server/main.cpp clients/client.cpp channels/channels.cpp ParseSide/topic_cmd.cpp ParseSide/kick_cmd.cpp server/handel_bot.cpp

OBJ = ${SRC:.cpp=.o}

CXX = c++

FLAGS =  -std=c++98 -Wall -Wextra -Werror  

RM = rm -f

NAME = ircserv

all:${NAME}  

${NAME}:${OBJ}
	${CXX} ${FLAGS} ${OBJ} -o ${NAME}

%.o: %.cpp server/server.hpp ParseSide/ParseSide.hpp clients/client.hpp channels/channel.hpp
	${CXX} ${FLAGS} -c $< -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all