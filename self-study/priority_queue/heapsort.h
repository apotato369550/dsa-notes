#ifndef HEAPSORT
#define HEAPSORT

#define MAX 21

typedef struct {
    int elem[MAX];
    int lastElem;
} Heap;

// i wonder if we can replace heapify up/down with regular heapfiy
void initialize(Heap *M);
void insert(Heap *M, int x);
int deleteMin(Heap *M);
void makeNull(Heap *M);
void heapify(Heap *M, int i);

#endif