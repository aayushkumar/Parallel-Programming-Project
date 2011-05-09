#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void quicksort(point** arr, int low, int high,int numBusyThreads, int MAX_THREADS);
void print_points(point** array,int n);
