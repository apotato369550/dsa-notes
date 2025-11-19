#include "minheap.h"

void initialize(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Minheap *M, int x) {
    // bug: off by one error on M->lastElem >= MAX
    // fix: M->lastElem >= MAX - 1
    if (M->lastElem >= MAX) return;
    M->elem[++M->lastElem] = x;
    heapifyUp(M, M->lastElem);
}


int deleteMin(Minheap *M) {
    // bug: no return type for int function
    // fix: return EMPTY instead
    if (M->lastElem < 0 ) return EMPTY;
    // bug: semantic error. variable named 'max' instead of 'min'
    int min = M->elem[0];
    M->elem[0] = M->elem[M->lastElem--];
    heapifyDown(M, 0);
    return min;
}

void makeNull(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void heapifyUp(Minheap *M, int i) {
    if (i == 0) return;
    int child = i;
    int parent = floor((child - 1) / 2);
    while (i != 0 && M->elem[child] < M->elem[parent]) {
        int temp = M->elem[child];
        M->elem[child] = M->elem[parent];
        M->elem[parent] = temp;

        // bug: forgot to reassign values for child and parent :((
        // fix: reassign child with parent, and parent using the parent formula
        child = parent;
        parent = floor((child - 1) / 2);
    }
}


