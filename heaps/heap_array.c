#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HEAP_ERROR INT_MIN

typedef struct {
    int *minHeap;
    int count;
    int size;
} MinHeap;

// notes for minheaps:
// given "node" at index i:
// parent = (i - 1) / 2
// left child = 2i + 1
// right child = 2i + 2

// create/destroy minheap
MinHeap *createMinHeap(int size);
void destroyMinHeap(MinHeap *minHeap);

// insertion, extraction, and peeking
int insertMinHeap(MinHeap *minHeap, int value);
int extractMin(MinHeap *minHeap);
int peekMin(MinHeap *minHeap);

// heapify functions
int heapifyUp(MinHeap *minHeap, int index);
int heapifyDown(MinHeap *minHeap, int index);

// getter functions
int getParentIndex(int index);
int getLeftChildIndex(int index);
int getRightChildIndex(int index);

// other functions
int isEmpty(MinHeap *minHeap);
int isFull(MinHeap *minHeap);
void printHeap(MinHeap *minHeap);

int main() {

    return 0;
}

MinHeap *createMinHeap(int size) {
    MinHeap *newMinHeap = malloc(sizeof(MinHeap));
    if (newMinHeap == NULL) {
        printf("Failed to allocate memory for minheap...\n");
        return NULL;
    }
    newMinHeap->count = 0;
    newMinHeap->size = size;
    newMinHeap->minHeap = malloc(sizeof(int) * newMinHeap->size);
    return newMinHeap;
}


void destroyMinHeap(MinHeap *minHeap) {
    free(minHeap->minHeap);
    free(minHeap);
    return;
}

int insertMinHeap(MinHeap *minHeap, int value) {
    if (isFull(minHeap)) {
        printf("Minheap is full! Failed to insert...\n");
        return HEAP_ERROR;
    }
    minHeap->minHeap[minHeap->count] = value;
    heapifyUp(minHeap, minHeap->count);
    minHeap->count++;

    return value;
}

int extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap)) {
        printf("Minheap is empty! Failed to extract...\n");
        return HEAP_ERROR;
    }
}
int peekMin(MinHeap *minHeap);