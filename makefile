CC=gcc
CFLAGS= -Wall -O -g

malloc: src/main.c malloc.o block.o
	$(CC) $(CFLAGS) src/main.c malloc.o block.o -o malloc

malloc.o: src/malloc.c src/malloc.h
	$(CC) $(CFLAGS) -o malloc.o -c src/malloc.c

block.o: src/block.c src/block.h
	$(CC) $(CFLAGS) -o block.o -c src/block.c

clean:
	rm block.o malloc.o malloc
