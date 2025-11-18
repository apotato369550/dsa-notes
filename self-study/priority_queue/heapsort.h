#ifndef HEAPSORT
#define HEAPSORT

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <heap.h>

// i wonder if we can replace heapify up/down with regular heapfiy
void initialize(Heap *M);
void insert(Heap *M, int x);
int deleteMax(Heap *M);
void makeNull(Heap *M);
void heapify(Heap *M, int i);

#endif