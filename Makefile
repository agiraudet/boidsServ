NAME        := Boids

RTAUDIO_PATH := /opt/homebrew/Cellar/rtaudio/6.0.1
STK_PATH    := /opt/homebrew/opt/stk
SDL2_PATH   := /opt/homebrew/opt/sdl2

DEPS        := -framework CoreAudio -framework CoreFoundation -framework Cocoa -lSDL2 -lm -lstk -lrtaudio

BUILD_DIR   := ./build

SRCS_DIR    := ./srcs

SRCS        := main.cpp \
               Sky.cpp \
               Coord.cpp \
               Scene.cpp \
               StkWrap.cpp \
               Flock.cpp \
               Timer.cpp \
               RuleSet.cpp \
               Setting.cpp \
               Tonnetz.cpp \
               boids/ABoid.cpp \
               boids/Basic.cpp \
               boids/Goal.cpp \
               boids/Predator.cpp \
               boids/Prey.cpp

OBJS        := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

INC_DIRS    := ./includes \
               ./includes/boids \
               $(RTAUDIO_PATH)/include \
               $(STK_PATH)/include \
               $(STK_PATH)/include/stk \
               $(SDL2_PATH)/include \
               $(SDL2_PATH)/include/SDL2

INC_FLAGS   := $(addprefix -I, $(INC_DIRS))

LIB_DIRS    := $(RTAUDIO_PATH)/lib \
               $(STK_PATH)/lib \
               $(SDL2_PATH)/lib

LIB_FLAGS   := $(addprefix -L, $(LIB_DIRS))

CXXFLAGS    := -MD -O3 -g $(INC_FLAGS) -std=c++11

CXX         := clang++

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIB_FLAGS) $(DEPS) -o $@ -Wl,-rpath,$(RTAUDIO_PATH)/lib

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/boids

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
