#include "maxheap.h"

void initialize(Maxheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Maxheap *M, int x) {
    // bug: off by one error
    // fix: M->lastElem >= MAX - 1
    if (M->lastElem >= MAX - 1) return;
    M->elem[++M->lastElem] = x;
    heapifyUp(M, M->lastElem);
}

int deleteMax(Maxheap *M) {
    // bug: no return value
    // fix: return EMPTY
    if (M->lastElem < 0 ) return EMPTY;
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

        // bug: no variable update
        // fix: update child and parent
        child = parent;
        parent = floor((child - 1) / 2);
    }
}

void heapifyDown(Maxheap *M, int i) {
    // while i is not a leaf node, meaning:
    // it has left and right children

    // bug: wrong boundary check
    // fix: replace MAX with M->lastElem
    int leftChildIndex = (i * 2) + 1;
    bool hasLeftChild = leftChildIndex < M->lastElem && M->elem[leftChildIndex] != EMPTY;
    
    int rightChildIndex = (i * 2) + 2;
    bool hasRightChild = rightChildIndex < M->lastElem && M->elem[rightChildIndex] != EMPTY;
    int temp = 0;
    
    // update this condition to check if parent is still smaller than child
    while (hasLeftChild || hasRightChild) {
        int leftChild = hasLeftChild ? M->elem[leftChildIndex] : EMPTY;
        int rightChild = hasRightChild ? M->elem[rightChildIndex] : EMPTY;
        int smallerChild = EMPTY;
        if (hasLeftChild && hasRightChild) {
            // compare the two
            if (M->elem[i] < M->elem[leftChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[leftChildIndex];
                M->elem[leftChildIndex] = temp;
                i = leftChildIndex;
                leftChildIndex = (i * 2) + 1;
                hasLeftChild = leftChildIndex < MAX && M->elem[leftChildIndex] != EMPTY;
            } else if (M->elem[i] < M->elem[rightChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[rightChildIndex];
                M->elem[rightChildIndex] = temp;
                i = rightChildIndex;
                rightChildIndex = (i * 2) + 2;
                hasRightChild = rightChildIndex < MAX && M->elem[rightChildIndex] != EMPTY;
            } else {
                // bug: missing break statement
                // fix: add break statement
                break;
            }
        } else if (hasLeftChild) {
            if (M->elem[i] < M->elem[leftChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[leftChildIndex];
                M->elem[leftChildIndex] = temp;
                i = leftChildIndex;
                leftChildIndex = (i * 2) + 1;
                hasLeftChild = leftChildIndex < MAX && M->elem[leftChildIndex] != EMPTY;
            } else {
                // bug: missing break statement
                // fix: add break statement
                break;
            }  
        } else if (hasRightChild) {
            if (M->elem[i] < M->elem[rightChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[rightChildIndex];
                M->elem[rightChildIndex] = temp;
                i = rightChildIndex;
                rightChildIndex = (i * 2) + 2;
                hasRightChild = rightChildIndex < MAX && M->elem[rightChildIndex] != EMPTY;
            } else {
                // bug: missing break statement
                // fix: add break statement
                break;
            }
        } 
    }
    // i think this logic is sound, but it's very redundant HAHAHAHAHA
}
