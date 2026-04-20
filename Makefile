CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
TARGET = shell
SRC = shell.c
OBJ = shell.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re
