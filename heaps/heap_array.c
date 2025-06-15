#include <stdio.h>
#include <stdlib.h>

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

MinHeap *createMinHeap(int size);
void destroyMinHeap(MinHeap *minHeap);

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
    return
}
