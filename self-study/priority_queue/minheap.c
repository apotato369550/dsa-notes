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


void heapifyDown(Minheap *M, int i) {

    // while i is not a leaf node, meaning:
    // it has left and right children
    int leftChildIndex = (i * 2) + 1;
    bool hasLeftChild = leftChildIndex < M->lastElem && M->elem[leftChildIndex] != EMPTY;
    
    int rightChildIndex = (i * 2) + 2;
    bool hasRightChild = rightChildIndex < M->lastElem  && M->elem[rightChildIndex] != EMPTY;
    int temp = 0;
    
    // update this condition to check if parent is still smaller than child
    while (hasLeftChild || hasRightChild) {
        // how do we do this without a break statement??
        // maybe delegate checking if pot to another function??
        // i wanna do this right
        int leftChild = hasLeftChild ? M->elem[leftChildIndex] : EMPTY;
        int rightChild = hasRightChild ? M->elem[rightChildIndex] : EMPTY;
        int smallerChild = EMPTY;
        if (hasLeftChild && hasRightChild) {
            // bug: apparently, when both children exist, we need to find the smaller child
            // if the parent is bigger than the child, swap, otherwise, break.
            int smallerChildIndex = (M->elem[leftChildIndex] > M->elem[rightChildIndex]) ? rightChildIndex : leftChildIndex;
            if (M->elem[i] > M->elem[smallerChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[smallerChildIndex];
                M->elem[smallerChildIndex] = temp;
                i = smallerChildIndex;
            } else {
                break;
            }
        } else if (hasLeftChild) {
            if (M->elem[i] > M->elem[leftChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[leftChildIndex];
                M->elem[leftChildIndex] = temp;
                i = leftChildIndex;
                leftChildIndex = (i * 2) + 1;
                hasLeftChild = leftChildIndex < MAX && M->elem[leftChildIndex] != EMPTY;
            } else {
                // bug: forgot to break if POT is satisfied
                // fix: break statement
                break;
            }
        } else if (hasRightChild) {
            if (M->elem[i] > M->elem[rightChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[rightChildIndex];
                M->elem[rightChildIndex] = temp;
                i = rightChildIndex;
                rightChildIndex = (i * 2) + 2;
                hasRightChild = rightChildIndex < MAX && M->elem[rightChildIndex] != EMPTY;
            } else {
                // bug: forgot to break if POT is satisfied
                // fix: break statement
                break;
            }
        } 
        // bug: forgot to update for next iteration:((
        // fix: update next iteration
        leftChildIndex = (i * 2) + 1;
        hasLeftChild = leftChildIndex < M->lastElem;
        
        int rightChildIndex = (i * 2) + 2;
        hasRightChild = rightChildIndex < M->lastElem;
    }
    // i think this logic is sound, but it's very redundant HAHAHAHAHA
}
