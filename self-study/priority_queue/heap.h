#ifndef MY_HEAP
#define MY_HEAP

#define MAX 21
#define EMPTY INT_MIN

typedef struct {
    int elem[MAX];
    int lastElem;
} Heap, Minheap, MaxHeap;

#endif