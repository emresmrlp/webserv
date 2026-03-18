# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 15:49:15 by ysumeral          #+#    #+#              #
#    Updated: 2026/03/18 09:18:45 by ysumeral         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX 		=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
SRC			=	src/main.cpp \
				src/Connection.cpp \
				src/HTTPRequest.cpp
OBJ			=	$(SRC:.cpp=.o)
NAME		=	webserv

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re