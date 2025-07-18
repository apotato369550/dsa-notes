#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HEAP_ERROR INT_MIN
#define HEAP_EMPTY INT_MIN + 1

typedef struct Graph {
    int n;
    int **edges;
} Graph, *GraphPointer;

// we need a minheap to store the lowest value
typedef struct {
    int *minHeap;
    int count;
    int size;
} MinHeap;


// graph builder functions
GraphPointer createGraph(int n);
void destroyGraph(GraphPointer graph);
void printGraph(GraphPointer graph);
int hasEdge(GraphPointer graph, int from, int to);
int addEdge(GraphPointer graph, int from, int to, int weight);
int removeEdge(GraphPointer graph, int from, int to);

// graph helper functions
int hasVertex(GraphPointer graph, int vertex);
int isVisited(int vertex, int *visited);
void resetArray(int *array, int n, int value);

// minheap builder
MinHeap *createMinHeap(int size);
void destroyMinHeap(MinHeap **minHeap);
void printMinHeapAsArray(MinHeap *minHeap);

// minheap helper functions

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

// actual algorithms
void dijkstra_explore(GraphPointer graph, int start, int distances[], int parent[], MinHeap minheap);
int dijkstra_target(GraphPointer graph, int start, int target, int distances[], int parent[], MinHeap minheap);

// path printer function
void printPath(int start, int target, int *parent);

/*
         0
       /   \
      1     2
     / \   / \
    3   4 5   6
         \   /
          7
           \
            8
           /
          9

10 - 11 - 12   (Disconnected component)
        |
       13
         \
         14

15 - 16 - 17 - 18 - 19   (Linear tail)

 */

int main() {
    Graph *graph = createGraph(20);

    // Main component
    addEdge(graph, 0, 1, 2); addEdge(graph, 1, 0, 2);
    addEdge(graph, 0, 2, 4); addEdge(graph, 2, 0, 4);

    addEdge(graph, 1, 3, 3); addEdge(graph, 3, 1, 3);
    addEdge(graph, 1, 4, 1); addEdge(graph, 4, 1, 1);

    addEdge(graph, 2, 5, 6); addEdge(graph, 5, 2, 6);
    addEdge(graph, 2, 6, 2); addEdge(graph, 6, 2, 2);

    addEdge(graph, 4, 7, 2); addEdge(graph, 7, 4, 2);
    addEdge(graph, 6, 7, 1); addEdge(graph, 7, 6, 1);

    addEdge(graph, 7, 8, 4); addEdge(graph, 8, 7, 4);
    addEdge(graph, 9, 8, 3); addEdge(graph, 8, 9, 3);

    // Disconnected subgraph (cluster)
    addEdge(graph, 10, 11, 1); addEdge(graph, 11, 10, 1);
    addEdge(graph, 11, 12, 2); addEdge(graph, 12, 11, 2);
    addEdge(graph, 11, 13, 3); addEdge(graph, 13, 11, 3);
    addEdge(graph, 13, 14, 4); addEdge(graph, 14, 13, 4);

    // Linear chain tail
    addEdge(graph, 15, 16, 2); addEdge(graph, 16, 15, 2);
    addEdge(graph, 16, 17, 2); addEdge(graph, 17, 16, 2);
    addEdge(graph, 17, 18, 1); addEdge(graph, 18, 17, 1);
    addEdge(graph, 18, 19, 3); addEdge(graph, 19, 18, 3);

    printGraph(graph);

    return 0;
}


GraphPointer createGraph(int n) {
    // the pointers?? don't?? make?? sense??
    Graph *graph = malloc(sizeof(graph));
    if (graph == NULL) {
        return NULL;
    }
    graph->n = n;

    // allocate stuff for matrix using calloc
    graph->edges = calloc(sizeof(int*), graph->n);

    if (graph->edges == NULL) {
        return NULL;
    }

    for (int i = 0; i < graph->n; i++) {
        graph->edges[i] = calloc(sizeof(int), graph->n);
        if (graph->edges[i] == NULL) {
            destroyGraph(graph);
            return NULL;
        }
    }
    return graph;
}

void destroyGraph(GraphPointer graph) {
    if (graph->edges == NULL) {
        free(graph);
        return;
    }

    for (int i = 0; i < graph->n; i++) {
        if (graph->edges[i] != NULL) {
            free(graph->edges[i]);
        }
    }
    free(graph);
    return;
}

// change i, j to from, to
// change graph to *graph, since it'll be dynamically allocated
void printGraph(GraphPointer graph) {
    printf("----- START OF GRAPH -----\n");
    for (int from = 0; from < graph->n; from++) {
        for (int to = 0; to < graph->n; to++) {
            printf("%d ", graph->edges[from][to]);
        }
        printf("\n");
    }
    printf("----- END OF GRAPH -----\n");
}

int hasEdge(GraphPointer graph, int from, int to) {
    if (from >= graph->n || to >= graph->n) {
        return 0;
    }
    return graph->edges[from][to];
}

int addEdge(GraphPointer graph, int from, int to, int weight) {
    if (hasEdge(graph, from, to)) {
        printf("Already has edge...\n");
        return 0;
    }
    if (from >= graph->n || to >= graph->n) {
        printf("Index out of bounds!\n");
        return 0;
    }

    graph->edges[from][to] = weight;
    printf("Edge created!\n");

    return 1;
}


int removeEdge(GraphPointer graph, int from, int to) {
    if (!hasEdge(graph, from, to)) {
        return 0;
    }
    if (from >= graph->n || to >= graph->n) {
        return 0;
    }

    graph->edges[from][to] = 0;

    return 1;
}

int hasVertex(GraphPointer graph, int vertex) {
    return vertex >= graph->n ? 0 : 1;
}

int isVisited(int vertex, int *visited) {
    return visited[vertex];
}

void resetArray(int *array, int n, int value) {
    for (int i = 0; i < n; i++) {
        array[i] = value;
    }
}

// minheap builder
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
            // replace + with ,
            printf("%d ", minHeap->minHeap[i]);
        } else {
            printf("(empty) ");
        }
    }
    printf("\n");
}

// minheap helper functions

// insertion, extraction, and peeking
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
    return minHeap->minHeap[0];
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
            // replaced index with parentIndex
            leftChildIndex = getLeftChildIndex(parentIndex);
            rightChildIndex = getRightChildIndex(parentIndex);
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

int isEmpty(MinHeap *minHeap) {
    return minHeap->count == 0 ? 1 : 0;
}

int isFull(MinHeap *minHeap) {
    return minHeap->count >= minHeap->size - 1 ? 1 : 0;
}



void dijkstra_explore(GraphPointer graph, int start, int distances[], int parent[], MinHeap minheap) {
    // initialize:
    // distance as infinity for all nodes
    // parent as -1 for all nodes
    // visited as 0 for all nodes except start
    // push start into minheap/minheap

    // while the minheap is not empty:



    return;
}

void dijkstra_explore(GraphPointer graph, int start, int distances[], int parent[], MinHeap minheap) {

    return 0;
}

void printPath(int start, int target, int *parent) {
    if (start == target) {
        printf("%d", start);
        return;
    }   
    printPath(start, parent[target], parent);
    printf(" -> %d", target);
}