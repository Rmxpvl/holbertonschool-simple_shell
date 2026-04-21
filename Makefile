CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
TARGET = hsh
SRC = shell.c _getenv.c
OBJ = shell.o _getenv.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re
