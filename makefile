PROJECT_NAME = test #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c11 -O3

OBJECTS = ttt.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

ttt.o: ttt.c

clean:
	rm -f $(PROJECT_NAME) *.o