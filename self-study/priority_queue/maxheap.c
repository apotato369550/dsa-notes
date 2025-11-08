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
void heapifyUp(Maxheap *M, int i) {
    if (i == 0) return;
    int child = i;
    int parent = floor((child - 1) / 2);
    while (i != 0 && M->elem[child] > M->elem[parent]) {
        int temp = M->elem[child];
        M->elem[child] = M->elem[parent];
        M->elem[parent] = temp;
    }
}

void heapifyDown(Maxheap *M, int i) {
    // while i is not a leaf node, meaning:
    // it has left and right children
    int leftChildIndex = (i * 2) + 1;
    bool hasLeftChild = leftChildIndex < MAX && M->elem[leftChildIndex] != EMPTY;
    
    int rightChildIndex = (i * 2) + 2;
    bool hasRightChild = rightChildIndex < MAX && M->elem[rightChildIndex] != EMPTY;
    
    // update this condition to check if parent is still smaller than child
    while (hasLeftChild || hasRightChild) {
        int leftChild = hasLeftChild ? M->elem[leftChildIndex] : EMPTY;
        int rightChild = hasRightChild ? M->elem[rightChildIndex] : EMPTY;
        int smallerChild = EMPTY;
        if (hasLeftChild && hasRightChild) {
            // compare the two
        } else if (hasLeftChild) {
            // 
        } else if (hasRightChild) {

        }
    }
    return;
}