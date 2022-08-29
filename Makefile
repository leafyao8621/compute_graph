CPP = clang++
CPPFLAGS = -Wall -Wextra -pedantic -Werror
SRC = $(wildcard src/core/*.cpp) $(wildcard src/core/*/*.cpp) src/main.cpp
OBJ = $(SRC:.cpp=.o)
BIN = main

%.o: %.cpp
	$(CPP) -g -c $(CPPFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN)

.PHONY: clean
clean:
	@rm $(OBJ)
	@rm $(BIN)
