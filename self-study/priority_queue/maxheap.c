#include "maxheap.h"

void initialize(Maxheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Maxheap *M, int x);
int deleteMax(Maxheap *M);

void makeNull(Maxheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void heapifyUp(Maxheap *M, int i);
void heapifyDown(Maxheap *M, int i);