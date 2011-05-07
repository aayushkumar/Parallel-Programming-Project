# the compiler to use.
CC=gcc
# FLAGS.
CFLAGS=-c 
LINK=-lm

all: clean final

final: QuadEdge.o MemoryPool.o  Delaunay.o
	cc -lm QuadEdge.o MemoryPool.o  Delaunay.o -o delaunay

Delaunay.o: Delaunay.c
	$(CC) $(CFLAGS)  Delaunay.c

MemoryPool.o: MemoryPool.c
	$(CC) $(CFLAGS)  MemoryPool.c

QuadEdge.o: QuadEdge.c
	$(CC) $(CFLAGS)  QuadEdge.c


clean:
	rm -rf *.o

#final command  "cc -fopenmp  driver.c -L. -lpsearch -o test"



