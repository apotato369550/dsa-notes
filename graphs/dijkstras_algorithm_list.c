#include <stdio.h>
#include <stdlib.h>

// gotta figure out the struct declarations

// actual node

// heapnodes??
typedef struct HeapNode {
    char vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode *minHeap;
    int count;
    int size;
} MinHeap;

// gotta figure out the function prototypes
MinHeap *createMinHeap(int size);
void resetMinHeap(MinHeap *minHeap);
void destroyMinHpea(MinHeap **minHeap);
void printMinHeapAsArray(MinHeap *minHeap);

// include minheap helper functions

int insertMinHeap(MinHeap *MinHeap, char vertex, int distance);
HeapNode extractMin(MinHeap *minHeap);

// heapify functions
void heapifyUp(MinHeap *minHeap, int index);
void heapifyDown(MinHeap *minHeap, int index);

// getter functions
int getParentIndex(int index);
int getLeftChildIndex(int index);
int getRightChildIndex(int index);

// other functions
int isEmpty(MinHeap *minHeap);
int isFull(MinHeap *minHeap);

int main() {
    return 0;
}