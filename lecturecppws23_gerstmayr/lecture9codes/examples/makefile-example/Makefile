CC=gcc
CFLAGS=-I.

run: a.o b.o
	gcc -o $@ a.o b.o

.PHONY: clean
clean:
	rm -f *.o run
