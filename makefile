# compiler
CC = g++

# controls whether to build in debug or release mode
BUILD ?= release

# compiler flags for debug/release
ifeq ($(BUILD), release)
	CFLAGS = -O2
else
	CFLAGS = -O0 -g
endif

# linker flags for debug/release
ifeq ($(BUILD), release)
	LFLAGS = -O2
else
	LFLAGS = -O0 -g
endif

# general flags
FLAGS = -Wall -Wextra -std=c++14

# flags for adding included dirs and lib dirs
INCLUDE_DIRS = C:/glew/include C:/glfw/include
LIBS_DIRS = C:/glew/bin/Release/Win32 C:/glfw/lib-mingw

# libs to link to
LIBS = glew32 glfw3 GL

# source files
SRC = main.cpp Triangle.cpp Window.cpp

# resulting obj files
OBJ = $(SRC:%.cpp=%.o)

# resulting executable
EXE = run

.PHONY: makeDir clean

$(BUILD): makeDir $(OBJ)
	$(CC) -o $(BUILD)/$(EXE) $(FLAGS) $(LFLAGS) $(LIBS_DIRS:%=-L%) $(LIBS:%=-l%) $(OBJ:%=$(BUILD)/%)

main.o: makeDir main.cpp Triangle.o Window.o Vector.hpp
	$(CC) $(INCLUDE_DIRS:%=-I%) -c main.cpp -o $(BUILD)/$@ $(FLAGS) $(CFLAGS)

Triangle.o: makeDir Triangle.cpp Triangle.hpp Vector.hpp
	$(CC) $(INCLUDE_DIRS:%=-I%) -c Triangle.cpp -o $(BUILD)/$@ $(FLAGS) $(CFLAGS)

Window.o: makeDir Window.cpp Window.hpp Vector.hpp
	$(CC) $(INCLUDE_DIRS:%=-I%) -c Window.cpp -o $(BUILD)/$@ $(FLAGS) $(CFLAGS)

makeDir:
	mkdir -p $(BUILD)

clean:
	\rm -f $(BUILD)/*.o $(BUILD)/$(EXE)
