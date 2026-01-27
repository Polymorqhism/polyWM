CC = gcc
CFLAGS = -Wall -g
LIBS = -lX11
TARGET = build/polyWM
SRC = src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)


clean:
	rm -f $(TARGET)
