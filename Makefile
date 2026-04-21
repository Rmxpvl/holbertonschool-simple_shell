CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
TARGET = hsh
SRC = shell.c _getenv.c path.c execute.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re
