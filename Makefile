SRC=./src/*.c
INCLUDE=-I./include/
BIN=./bin
EXTRA_FLAGS = -Wall -Werror -Wextra

all:
	gcc $(SRC) -g -lm $(EXTRA_FLAGS) $(INCLUDE) -o $(BIN)

run:
	$(BIN)

clean:
	rm $(BIN)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BIN)