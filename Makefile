CC = clang
CFLAGS = -Wall -Wextra -std=c99 -O2 -I. -Ibinds
LIBS = -lX11

BIN = build/polyWM

SRC := $(shell find . -name "*.c")
OBJ := $(patsubst ./%.c, build/%.o, $(SRC))
DEPS := $(OBJ:.o=.d)

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p build
	$(CC) $(OBJ) $(LIBS) -o $(BIN)

# compile + generate dependency files (.d)
build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# include dependency files (auto header tracking)
-include $(DEPS)

clean:
	rm -rf build

move: all
	mv $(BIN) ~/polyWM-dev
