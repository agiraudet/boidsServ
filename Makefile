# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2022/12/05 11:11:23 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	Boids

DEPS		:=	-lSDL2 -lm -lstk -lasound

BUILD_DIR	:=	./build

SRCS_DIR	:=	./srcs

SRCS		:=	main.cpp \
				boids/ABoid.cpp \
				boids/Basic.cpp \
				boids/Predator.cpp\
				Coord.cpp \
				Flock.cpp \
				RuleSet.cpp \
				Setting.cpp \
				Scene.cpp \
				Sky.cpp \
				StkWrap.cpp \
				Timer.cpp

OBJS		:=	$(SRCS:%.cpp=$(BUILD_DIR)/%.o)

INC_DIRS	:=	./includes \
				./includes/boids

INC_FLAGS	:=	$(addprefix -I, $(INC_DIRS))

CXXFLAGS	:=	-MD -O3 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-private-field -D __LINUX_ALSA__ -g $(INC_FLAGS)

CXX			:=	clang++

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(DEPS) -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/boids

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
