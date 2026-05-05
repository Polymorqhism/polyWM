CC = clang
FLAGS = -Wall -Wextra -std=c99 -O2
LIBS = -lxcb
OBJS = build/polywm.o build/util.o
BIN = build/polyWM

$(BIN): $(OBJS)
	mkdir -p build
	$(CC) $(OBJS) $(LIBS) -o $(BIN)

build/polywm.o: polywm.c polywm.h util.h config.h
	mkdir -p build
	$(CC) $(FLAGS) -c $< -o $@

build/util.o: util.c util.h polywm.h
	mkdir -p build
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean move

clean:
	rm -rf build/*

move:
	mv $(BIN) ~/polyWM-dev
