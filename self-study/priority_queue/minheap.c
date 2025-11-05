#include "minheap.h"

void initialize(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Minheap *M, int x) {
    if (M->lastElem >= MAX) return;
    M->elem[++M->lastElem] = x;
    heapifyUp(M, M->lastElem);
}


int deleteMin(Minheap *M) {
    if (M->lastElem < 0 ) return;
    int max = M->elem[0];
    M->elem[0] = M->elem[M->lastElem--];
    heapifyDown(M, 0);
    return max;
}

void makeNull(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void heapifyUp(Minheap *M, int i);
void heapifyDown(Minheap *M, int i);
