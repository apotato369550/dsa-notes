#include "maxheap.h"

void initialize(Maxheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Maxheap *M, int x) {
    if (M->lastElem >= MAX) return;
    M->elem[++M->lastElem] = x;
    heapifyUp(M, M->lastElem);
}

int deleteMax(Maxheap *M) {
    if (M->lastElem < 0 ) return;
    int max = M->elem[0];
    M->elem[0] = M->elem[M->lastElem--];
    heapifyDown(M, 0);
    return max;
}

void makeNull(Maxheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

// helpers
void heapifyUp(Maxheap *M, int i);
void heapifyDown(Maxheap *M, int i);