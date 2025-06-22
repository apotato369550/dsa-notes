#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HEAP_ERROR INT_MIN
#define HEAP_EMPTY INT_MIN + 1

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
void destroyMinHeap(MinHeap **minHeap);

// printing functions
// how does one go about printing a minheap??
void printMinHeapAsArray(MinHeap *minHeap);
void printTabs(int tabs);
void printMinHeapAsTree(MinHeap *minHeap, int index, int tabs);

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

// populate function
void populateMinHeap(MinHeap *minHeap);

int main() {
    // maybe perform realloc whenever new element is added??
    MinHeap *minHeap = createMinHeap(10);
    populateMinHeap(minHeap);

    // do some printing in between to debug all the functions related to insertion
    printf("Printing minheap in array form: \n");
    printMinHeapAsArray(minHeap);

    // printf("Printing minheap in tree form: \n");
    // printMinHeapAsTree(minHeap, 0, 0);

    destroyMinHeap(&minHeap);
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

    // use calloc :V OR! SET IT TO EMPTY
    newMinHeap->minHeap = malloc(sizeof(int) * newMinHeap->size);
    for (int i = 0; i < newMinHeap->size; i++) {
        newMinHeap->minHeap[i] = HEAP_EMPTY;
    }
    return newMinHeap;
}


void destroyMinHeap(MinHeap **minHeap) {
    free((*minHeap)->minHeap);
    free((*minHeap));
    (*minHeap) = NULL;
    return;
}

void printMinHeapAsArray(MinHeap *minHeap) {
    for (int i = 0; i < minHeap->count; i++) {
        if (minHeap->minHeap[i] != HEAP_EMPTY) {
            printf("%d " + minHeap->minHeap[i]);
        }
    }
    printf("\n");
}

void printTabs(int tabs) {
    for (int i = 0; i < tabs; i++) {
        printf("\t");
    }
}

void printMinHeapAsTree(MinHeap *minHeap, int index, int tabs) {
    // if index is greater or equal to than the heap's size, 
    // print tabs and empty, then return
    if (index > minHeap->size) {
        printTabs(tabs);
        printf("----- EMPTY ----- \n");
        return;
    }

    // by default, it should:
    // get the right child = 2 * index + 2
    int rightChildIndex = 2 * index + 2;

    // get the left child = 2 * index + 1
    int leftChildIndex = 2 * index + 1;

    // recurse with right, incrementing tabs
    printMinHeapAsTree(minHeap, rightChildIndex, tabs + 1);
    // print current tabs (to indent current index)
    printTabs(tabs);
    // print the current value at index
    if (minHeap->minHeap[index] != HEAP_EMPTY) {
        printf("%d \n", minHeap->minHeap[index]);
    } else {
        printf("----- EMPTY ----- \n");
    }
    // recurse with left child, incrementing tabs again
    printMinHeapAsTree(minHeap, leftChildIndex, tabs + 1);
}

int insertMinHeap(MinHeap *minHeap, int value) {
    if (isFull(minHeap)) {
        printf("Minheap is full! Failed to insert...\n");
        return HEAP_ERROR;
    }
    minHeap->minHeap[minHeap->count] = value;
    if (heapifyUp(minHeap, minHeap->count)) {
        printf("Successfully heapified up!\n");
    } else {
        printf("Failed to heapfiy up...");
    }
    minHeap->count++;

    return value;
}

int extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap)) {
        printf("Minheap is empty! Failed to extract...\n");
        return HEAP_ERROR;
    }
    int minimumValue = minHeap->minHeap[0];
    int lastElement = minHeap->minHeap[minHeap->count - 1];
    minHeap->minHeap[0] = lastElement;
    minHeap->count -= 1;
    if (heapifyDown(minHeap, 0)) {
        printf("Successfully heapified down!\n");
    } else {
        printf("Failed to heapify down...\n");
    }
    return minimumValue;
}
int peekMin(MinHeap *minHeap) {
    if (isEmpty(minHeap)) {
        printf("Minheap is empty! Failed to peek...\n");
        return HEAP_ERROR;
    }
    return minHeap->minHeap[minHeap->count - 1];
}


// heapify functions
int heapifyUp(MinHeap *minHeap, int index) {
    // start at index (ideally the last element inserted) = count - 1
    // compare element at index vs parent element
    int childIndex = index;
    int parentIndex = getParentIndex(index);

    // while we still have a valid parent index...
    while (parentIndex >= 0) {
        // check if we need to swap:
        int parent = minHeap->minHeap[parentIndex];
        int child = minHeap->minHeap[childIndex];
    
        if (child < parent) {
            // perform the swap 
            minHeap->minHeap[childIndex] = parent;
            minHeap->minHeap[parentIndex] = child;

            // move child to parent
            childIndex = parentIndex;
            parentIndex = getParentIndex(childIndex);
        } else {
            // the minheap should be alright
            break;
        }
    }
    return 1;
}
int heapifyDown(MinHeap *minHeap, int index) {
    // when the current node has at least one child
    
    // parent = (i - 1) / 2
    // left child = 2i + 1
    // right child = 2i + 2

    int parentIndex = index;
    int leftChildIndex = getLeftChildIndex(index);
    int rightChildIndex = getRightChildIndex(index);

    while (leftChildIndex < minHeap->count || rightChildIndex < minHeap->count) {
        // find the smaller child (or only child)
        // if left and right are valid, compare left and right
        // otherwise, isolate and check which is invalid, and assign that instead to childIndex
        int childIndex = -1;
        if (leftChildIndex < minHeap->count && rightChildIndex < minHeap->count) {
            int leftChild = minHeap->minHeap[leftChildIndex];
            int rightChild = minHeap->minHeap[rightChildIndex];

            if (leftChild < rightChild) {
                childIndex = leftChildIndex;
            } else {
                childIndex = rightChildIndex;
            }
        } else {
            if (leftChildIndex < minHeap->count) {
                // left must be valid, right must be invalid
                childIndex = leftChildIndex;
            } else {
                // right must be valid.
                childIndex = rightChildIndex;
            }
        }
        int child = minHeap->minHeap[childIndex];
        int parent = minHeap->minHeap[parentIndex];
        // if the current node's value > smaller child, 
        if (parent > child) {
            // perform swap
            int temp = child;
            minHeap->minHeap[childIndex] = parent;
            minHeap->minHeap[parentIndex] = temp;
            // move index to child index
            parentIndex = childIndex;

            // recalculate left and right child indices
            leftChildIndex = getLeftChildIndex(index);
            rightChildIndex = getRightChildIndex(index);
        } else {
            break;
        // otherwise, minheap property should be restored
        }
    }
    return 1;
}

// getter functions
int getParentIndex(int index) {
    return (index - 1) / 2;
}

int getLeftChildIndex(int index) {
    return (2 * index) + 1;
}

int getRightChildIndex(int index) {
    return (2 * index) + 2;
}

void populateMinHeap(MinHeap *minHeap) {
    int array[] = {5, 10, 15, 20, 25, 3, 6, 9, 12};
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        if (insertMinHeap(minHeap, array[i]) != HEAP_ERROR) { 
            printf("Successfully inserted value %d to minheap\n", array[i]);
        } else {
            printf("Failed to insert value %d to minheap.\n", array[i]);
        }
    }
    return;
}

int isEmpty(MinHeap *minHeap) {
    return minHeap->count == 0 ? 1 : 0;
}

int isFull(MinHeap *minHeap) {
    return minHeap->count >= minHeap->size - 1 ? 1 : 0;
}