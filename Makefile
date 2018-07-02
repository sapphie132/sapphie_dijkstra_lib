CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -g
LDFLAGS=

test: test.c minheap.o
	$(CC) $(CFLAGS) -o $@ $^
minheap.o: minheap.cpp minheap.h

clean: 
	rm *.o test
