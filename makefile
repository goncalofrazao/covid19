PROJECT_NAME = covid19 #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c11 -g #-O3

OBJECTS = main.o input.o new_struct.o order_data.o select_data.o restrict_data.o console.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c structures.h
input.o: input.c input.h
new_struct.o: new_struct.c new_struct.h
order_data.o: order_data.c order_data.h
select_data.o: select_data.c select_data.h
restrict_data.o: restrict_data.c restrict_data.h
console.o: console.c console.h

clean:
	rm -f $(PROJECT_NAME) *.o