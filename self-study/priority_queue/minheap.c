#include "minheap.h"

void initialize(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Minheap *M, int x);
int deleteMax(Minheap *M);

void makeNull(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void heapifyUp(Minheap *M, int i);
void heapifyDown(Minheap *M, int i);
