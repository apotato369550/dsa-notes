#ifndef MAXHEAP
#define MAXHEAP

#include <limits.h>

#define MAX 21
#define EMPTY INT_MIN

typedef struct {
    int elem[MAX];
    int lastElem;
} Maxheap;

void initialize(Maxheap *M);
void insert(Maxheap *M, int x);
int deleteMax(Maxheap *M);
void makeNull(Maxheap *M);
void heapifyUp(Maxheap *M, int i);
void heapifyDown(Maxheap *M, int i);


#endif