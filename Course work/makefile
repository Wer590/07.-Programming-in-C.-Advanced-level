CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = main.c
OBJ = $(SRC:.c=.o math_utils.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lm

main.o: main.c math_utils.h
	$(CC) $(CFLAGS) -c $(SRC)

math_utils.o: math_utils.c math_utils.h
	$(CC) $(CFLAGS) -c math_utils.c

clean:
	del -f $(OBJ) $(TARGET).exe

