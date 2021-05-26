PROJECT_NAME = compare #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c11 -g -O3

OBJECTS = compare.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

compare.o: compare.c

clean:
	rm -f $(PROJECT_NAME) *.o