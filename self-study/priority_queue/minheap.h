#ifndef MINHEAP
#define MINHEAP

#include <limits.h>
#include <math.h>

#define MAX 23
#define EMPTY INT_MIN

typedef struct {
    int elem[MAX];
    int lastElem;
} Minheap;

void initialize(Minheap *M);
void insert(Minheap *M, int x);
int deleteMax(Minheap *M);
void makeNull(Minheap *M);
void heapifyUp(Minheap *M, int i);
void heapifyDown(Minheap *M, int i);


#endif