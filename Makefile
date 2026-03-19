# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/18 13:17:49 by ysumeral          #+#    #+#              #
#    Updated: 2026/03/19 13:14:46 by ysumeral         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_BLUE      =	\033[38;5;111m
P_PURPLE    =	\033[38;5;147m
P_AQUA      =	\033[38;5;159m
P_GREEN     =	\033[38;5;120m
P_PEACH     =	\033[38;5;222m
RESET       =	\033[0m
PREFIX      =	$(P_BLUE)(WEBSERV)$(RESET)

CXX         =   c++
CXXFLAGS    =   -Wall -Wextra -Werror -std=c++98
IFLAGS      =   -I include/core -I include/http
SRC_DIR     =   src/
OBJ_DIR     =   obj/
CORE_DIR    =   $(SRC_DIR)core/
HTTP_DIR    =   $(SRC_DIR)http/

CORE_SRC    =   $(SRC_DIR)main.cpp \
				$(CORE_DIR)Connection.cpp

HTTP_SRC    =   $(HTTP_DIR)Request.cpp \
				$(HTTP_DIR)AResponseBase.cpp \
				$(HTTP_DIR)StaticResponse.cpp \
				$(HTTP_DIR)AutoIndexResponse.cpp \
				$(HTTP_DIR)ErrorResponse.cpp

SRC         =   $(CORE_SRC) $(HTTP_SRC)
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
	@echo "$(P_BLUE) ██   ██ ███████ ██    ██     ██      ██ ███████ ████████ ███████ ███    ██  ██ ██  ██ $(RESET)"
	@echo "$(P_BLUE) ██   ██ ██       ██  ██      ██      ██ ██         ██    ██      ████   ██ ██   ██ ██ $(RESET)"
	@echo "$(P_BLUE) ███████ █████     ████       ██      ██ ███████    ██    █████   ██ ██  ██ ██   ██ ██ $(RESET)"
	@echo "$(P_BLUE) ██   ██ ██         ██        ██      ██      ██    ██    ██      ██  ██ ██ ██   ██    $(RESET)"
	@echo "$(P_BLUE) ██   ██ ███████    ██        ███████ ██ ███████    ██    ███████ ██   ████  ██ ██  ██ $(RESET)"
	@echo ""
	@echo "                   $(P_AQUA)--- A HIGH-PERFORMANCE HTTP SERVER PROJECT ---$(RESET)"
	@echo "                  $(P_PEACH)Developed by ysumeral, etorun, hhaciogl (C) 2026$(RESET)"
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