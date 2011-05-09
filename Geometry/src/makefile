# the compiler to use.
CC=mpicc
# FLAGS.
CFLAGS=-c -g 
LINK=-lm

all: clean parallel

sequential: QuadEdge.o MemoryPool.o  Delaunay.o
	$(CC) -lm QuadEdge.o MemoryPool.o  Delaunay.o -o delaunay

parallel: QuadEdge.o MemoryPool.o  Delaunay.o LinkedListNode.o LinkedList.o LinkedListIterator.o ParallelDelaunay.o
	$(CC) -lm QuadEdge.o MemoryPool.o  Delaunay.o LinkedListNode.o LinkedList.o LinkedListIterator.o ParallelDelaunay.o -o paralleldelaunay

Delaunay.o: Delaunay.c
	$(CC) $(CFLAGS)  Delaunay.c

MemoryPool.o: MemoryPool.c
	$(CC) $(CFLAGS)  MemoryPool.c

QuadEdge.o: QuadEdge.c
	$(CC) $(CFLAGS)  QuadEdge.c

LinkedListNode.o: LinkedListNode.c
	$(CC) $(CFLAGS)  LinkedListNode.c

LinkedList.o: LinkedList.c
	$(CC) $(CFLAGS)  LinkedList.c

LinkedListIterator.o: LinkedListIterator.c
	$(CC) $(CFLAGS)  LinkedListIterator.c

ParallelDelaunay.o: ParallelDelaunay.c
	$(CC) $(CFLAGS)  ParallelDelaunay.c


clean:
	rm -rf *.o

#final command  "cc -fopenmp  driver.c -L. -lpsearch -o test"
#gcc -o lines lines.c `pkg-config --libs --cflags gtk+-2.0`


