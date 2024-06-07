CC = gcc
CFLAGS = -Wall -Wextra

all: sudoku generate validate

sudoku: sudoku.o display.o
	$(CC) $(CFLAGS) -o sudoku sudoku.o display.o

generate: generate.o
	$(CC) $(CFLAGS) -o generate generate.o

validate: validate.o
	$(CC) $(CFLAGS) -o validate validate.o

sudoku.o: sudoku.c
	$(CC) $(CFLAGS) -c sudoku.c

generate.o: generate.c
	$(CC) $(CFLAGS) -c generate.c

validate.o: validate.c
	$(CC) $(CFLAGS) -c validate.c

display.o: display.c
	$(CC) $(CFLAGS) -c display.c

clean:
	rm -f *.o sudoku generate validate
	rm -f *.txt sudoku solution