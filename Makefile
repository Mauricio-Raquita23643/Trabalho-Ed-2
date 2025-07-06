# Makefile
CC=gcc
CFLAGS=-Wall -pg -g
OBJ=main.o hash.o

all: programa

programa: $(OBJ)
	$(CC) -o programa $(OBJ)

main.o: main.c hash.h
	$(CC) $(CFLAGS) -c main.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c

clean:
	rm -f *.o programa gmon.out
