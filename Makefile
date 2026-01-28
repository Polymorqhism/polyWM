CC = clang
FLAGS = -Wall -Wextra -std=c99 -O2
LIBS = -lX11
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

.PHONY: clean transfer

clean:
	rm -rf build/*


# Do not use this unless you are running in on a VM. If that is the case, you may need to modify 'wmfiles/' directory. This requires proper mounting of the VM to allow for shared directories.
transfer: $(BIN)
	mv $(BIN) wmfiles/

