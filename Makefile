# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2022/11/29 13:59:59 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	boids

DEPS		:=	-lSDL2 -lm

BUILD_DIR	:=	./build

SRCS_DIR	:=	./srcs

SRCS		:=	main.cpp \
				Boid.cpp \
				Coord.cpp \
				Flock.cpp \
				Setting.cpp \
				Scene.cpp \
				Sky.cpp \
				Timer.cpp

OBJS		:=	$(SRCS:%.cpp=$(BUILD_DIR)/%.o)

INC_DIRS	:=	./includes 

INC_FLAGS	:=	$(addprefix -I, $(INC_DIRS))

CXXFLAGS	:=	-MD -O3 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -g $(INC_FLAGS)

CXX			:=	clang++

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(DEPS) -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/cmds

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
