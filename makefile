PROJECT_NAME = covid19 #target file name

CC = gcc #compiler
CFLAGS = -Wall -std=c11 -O3

OBJECTS = main.o order_data.o select_data.o new_struct.o restrict_data.o input.o #objects

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

main.o: main.c
order_data.o: order_data.c order_data.h
select_data.o: select_data.c select_data.h
new_struct.o: new_struct.c new_struct.h
restrict_data.o:  restrict_data.c restrict_data.h
input.o: input.c input.h 

clean:
	rm -f $(PROJECT_NAME) *.o