PROJECT_NAME = covid19 #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c11 -g #-O3

OBJECTS = main.o input.o new_struct.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c structures.h
input.o: input.c input.h
new_struct.o: new_struct.c new_struct.h

c:
	rm -f $(PROJECT_NAME) *.o