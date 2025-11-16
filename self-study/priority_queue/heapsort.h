#ifndef HEAPSORT
#define HEAPSORT

#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define MAX 21
#define EMPTY INT_MIN

// ASSUMPTION: Maxheap :VVV
typedef struct {
    int elem[MAX];
    int lastElem;
} Heap;

// i wonder if we can replace heapify up/down with regular heapfiy
void initialize(Heap *M);
void insert(Heap *M, int x);
int deleteMax(Heap *M);
void makeNull(Heap *M);
void heapify(Heap *M, int i);

#endif