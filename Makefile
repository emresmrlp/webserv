# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/18 13:17:49 by ysumeral          #+#    #+#              #
#    Updated: 2026/06/06 10:14:59 by ysumeral         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_BLUE				=	\033[38;5;111m
P_PURPLE			=	\033[38;5;147m
P_AQUA				=	\033[38;5;159m
P_GREEN				=	\033[38;5;120m
P_PEACH				=	\033[38;5;222m
RESET				=	\033[0m
PREFIX				=	$(P_BLUE)(WEBSERV)$(RESET)
CXX					=	c++
CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98
IFLAGS				=	-I include \
						-I include/config \
						-I include/core \
						-I include/http \
						-I include/http/request \
						-I include/http/response
SRC_DIR				=	src/
OBJ_DIR				=	obj/
CONFIG_DIR			=	$(SRC_DIR)config/
CORE_DIR			=	$(SRC_DIR)core/
HTTP_DIR			=	$(SRC_DIR)http/
HTTP_REQUEST_DIR	=	$(HTTP_DIR)request/
HTTP_RESPONSE_DIR	=	$(HTTP_DIR)response/

CONFIG_SRC	=	$(CONFIG_DIR)ConfigServer.cpp \
				$(CONFIG_DIR)ConfigServerBuilder.cpp \
				$(CONFIG_DIR)ConfigLocation.cpp \
				$(CONFIG_DIR)ConfigLocationBuilder.cpp \
				$(CONFIG_DIR)Parser.cpp \
				$(CONFIG_DIR)Token.cpp 
	
CORE_SRC	=	$(SRC_DIR)main.cpp \
				$(CORE_DIR)Server.cpp \
				$(CORE_DIR)ServerHandler.cpp \
				$(CORE_DIR)Connection.cpp \
				$(CORE_DIR)Util.cpp

HTTP_SRC	=	$(HTTP_REQUEST_DIR)Request.cpp \
				$(HTTP_REQUEST_DIR)RequestBuilder.cpp \
				$(HTTP_RESPONSE_DIR)ResponseDispatcher.cpp \
				$(HTTP_RESPONSE_DIR)ResponseFactory.cpp \
				$(HTTP_RESPONSE_DIR)AResponseBase.cpp \
				$(HTTP_RESPONSE_DIR)OkResponse.cpp \
				$(HTTP_RESPONSE_DIR)ErrorResponse.cpp \
				$(HTTP_RESPONSE_DIR)RedirectResponse.cpp

SRC         =   $(CONFIG_SRC) $(CORE_SRC) $(HTTP_SRC)
OBJ         =   $(SRC:src/%.cpp=$(OBJ_DIR)%.o)
NAME        =   webserv

all: $(NAME)

$(OBJ_DIR)%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "$(PREFIX) $(P_PURPLE)Compiling:$(RESET) $(P_AQUA)$<$(RESET)"
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@
	@echo "$(P_GREEN)OK.$(RESET)"

$(NAME): $(OBJ)
	@echo "\n$(PREFIX) $(P_PEACH)Linking object files...$(RESET)"
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo ""
	@echo "$(P_BLUE) ██     ██ ███████ ██████  ███████ ███████ ██████  ██    ██ $(RESET)"
	@echo "$(P_BLUE) ██     ██ ██      ██   ██ ██      ██      ██   ██ ██    ██ $(RESET)"
	@echo "$(P_BLUE) ██  █  ██ █████   ██████  ███████ █████   ██████  ██    ██ $(RESET)"
	@echo "$(P_BLUE) ██ ███ ██ ██      ██   ██      ██ ██      ██   ██  ██  ██  $(RESET)"
	@echo "$(P_BLUE)  ███ ███  ███████ ██████  ███████ ███████ ██   ██   ████   $(RESET)"
	@echo ""
	@echo "      $(P_AQUA)------ A LOW-LEVEL HTTP SERVER PROJECT ------$(RESET)"
	@echo "        $(P_PEACH)Developed by ysumeral, beldemir (C) 2026$(RESET)"
	@echo ""
	@echo "$(PREFIX) $(P_GREEN)All done, webserv is ready!$(RESET)"
	@echo "$(PREFIX) $(P_AQUA)Usage: ./webserv <configuration file>$(RESET)"

clean:
	@echo "$(PREFIX) $(P_PURPLE)Cleaning objects...$(RESET)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(PREFIX) $(P_PURPLE)Cleaning binary...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re