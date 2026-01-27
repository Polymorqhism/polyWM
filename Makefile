CC = clang
FLAGS = -Wall -Wextra -std=c99 -O2
LIBS = -lX11
OBJS = build/polywm.o build/util.o
BIN = build/polywm

$(BIN): $(OBJS)
	mkdir -p build
	$(CC) $(OBJS) $(LIBS) -o $(BIN)

build/polywm.o: polywm.c polywm.h util.h config.h
	mkdir -p build
	$(CC) $(FLAGS) -c $< -o $@

build/util.o: util.c util.h polywm.h
	mkdir -p build
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean run install

clean:
	rm -rf build/*

run: $(BIN)
	./$(BIN)

install: $(BIN)
	cp $(BIN) /usr/local/bin/polywm
