#include <stdio.h>
#include <stdlib.h>

#define NO_VERTEX '*'
// gotta figure out the struct declarations

typedef struct GraphNode {
    char vertex;
    int weight;
    struct GraphNode *next;
} GraphNode, *GraphNodePointer;

typedef struct Graph {
    int n;
    GraphNodePointer adjacency_list;
} Graph, *GraphPointer;

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

GraphPointer createGraph(int n);
int destroyGraph(GraphPointer graph);
void printGraph(GraphPointer graph);
int hasVertex(GraphPointer graph, char vertex);
int hasEdge(GraphPointer graph, char from, char to);
int addEdge(GraphPointer graph, char from, char to, int weight);

// graph helper functions
int getIndexOfVertex(char vertex);
char getVertexOfIndex(int index);
GraphNode getVertexFromGraph(GraphPointer graph, char vertex);
void resetArray(int *array, int n, int value);

// gotta figure out the function prototypes
MinHeap *createMinHeap(int size);
void resetMinHeap(MinHeap *minHeap);
void destroyMinHeap(MinHeap **minHeap);
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

// actual algorithms
void dijkstra_explore(GraphPointer graph, char start, int *distances, int *parent, MinHeap *minheap);
int dijkstra_target(GraphPointer graph, char start, char target, int *distances, int *parent, MinHeap *minheap);

// path printer function
void printPath(char start, char target, int *parent);

// distance printer function
void printDistances(char start, int *distances, int n);

// print weight given a path 
void printWeightGivenPath(GraphPointer graph, char start, char target, int *parent);


/*
         A
       /   \
      B     C
     / \   / \
    D   E F   G
         \   /
          H
           \
            I
           /
          J

K - L - M   (Disconnected component)
    |
    N
     \
      O

P - Q - R - S - T   (Linear tail)
*/


int main() {
    // let's start by building the graph and displaying it :V
    Graph *graph = createGraph(20);

    // Main component
    addEdge(graph, 'A', 'B', 2); addEdge(graph, 'B', 'A', 2);
    addEdge(graph, 'A', 'C', 4); addEdge(graph, 'C', 'A', 4);

    addEdge(graph, 'B', 'D', 3); addEdge(graph, 'D', 'B', 3);
    addEdge(graph, 'B', 'E', 1); addEdge(graph, 'E', 'B', 1);

    addEdge(graph, 'C', 'F', 6); addEdge(graph, 'F', 'C', 6);
    addEdge(graph, 'C', 'G', 2); addEdge(graph, 'G', 'C', 2);

    addEdge(graph, 'E', 'H', 2); addEdge(graph, 'H', 'E', 2);
    addEdge(graph, 'G', 'H', 1); addEdge(graph, 'H', 'G', 1);

    addEdge(graph, 'H', 'I', 4); addEdge(graph, 'I', 'H', 4);
    addEdge(graph, 'J', 'I', 3); addEdge(graph, 'I', 'J', 3);

    // Disconnected subgraph (cluster)
    addEdge(graph, 'K', 'L', 1); addEdge(graph, 'L', 'K', 1);
    addEdge(graph, 'L', 'M', 2); addEdge(graph, 'M', 'L', 2);
    addEdge(graph, 'L', 'N', 3); addEdge(graph, 'N', 'L', 3);
    addEdge(graph, 'N', 'O', 4); addEdge(graph, 'O', 'N', 4);

    // Linear chain tail
    addEdge(graph, 'P', 'Q', 2); addEdge(graph, 'Q', 'P', 2);
    addEdge(graph, 'Q', 'R', 2); addEdge(graph, 'R', 'Q', 2);
    addEdge(graph, 'R', 'S', 1); addEdge(graph, 'S', 'R', 1);
    addEdge(graph, 'S', 'T', 3); addEdge(graph, 'T', 'S', 3);

    printGraph(graph);

    // initializing helper data structs
    int *distances = malloc(sizeof(int) * graph->n);
    int *parent = malloc(sizeof(int) * graph->n);
    MinHeap *minheap = createMinHeap(graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);

    // A
    dijkstra_explore(graph, 'A', distances, parent, minheap);
    printDistances('A', distances, graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);


    // O
    dijkstra_explore(graph, 'O', distances, parent, minheap);
    printDistances('O', distances, graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // Q
    dijkstra_explore(graph, 'Q', distances, parent, minheap);
    printDistances('Q', distances, graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // A - J
    dijkstra_target(graph, 'A', 'J', distances, parent, minheap);
    printPath('A', 'J', parent);
    // printWeightGivenPath(graph, 'A', 'J', parent);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    /*
    // K - O
    dijkstra_target(graph, 'K', 'O', distances, parent, minheap);
    printPath('K', 'O', parent);
    printWeightGivenPath(graph, 'K', 'O', parent);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // P - T
    dijkstra_target(graph, 'P', 'T', distances, parent, minheap);
    printPath('P', 'T', parent);
    printWeightGivenPath(graph, 'P', 'T', parent);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);
    */

    destroyGraph(graph);

    return 0;
}

GraphPointer createGraph(int n) {
    Graph *graph = malloc(sizeof(Graph));

    if (graph == NULL) {
        return NULL;
    }

    graph->n = n;
    graph->adjacency_list = malloc(sizeof(GraphNode) * graph->n);

    if (graph->adjacency_list == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        graph->adjacency_list[i].vertex = (char) ((int) 'A' + i);
        graph->adjacency_list[i].weight = 0;
        graph->adjacency_list[i].next = NULL;
    }   

    return graph;
}

int destroyGraph(GraphPointer graph) {
    free(graph->adjacency_list);
    free(graph);
}

void printGraph(GraphPointer graph) {
    printf("----- START OF GRAPH -----\n");
    for (int i = 0; i < graph->n; i++) {
        printf("Vertex %c: ", graph->adjacency_list[i].vertex);

        GraphNodePointer current = graph->adjacency_list[i].next;
        while (current != NULL) {
            printf("%c (%d)", current->vertex, current->weight);
            if (current->next != NULL) {
                printf(" -> ");
            }
            current = current->next;
        }

        printf("\n");
    }
    printf("----- END OF GRAPH -----\n");
    return;
}

int hasVertex(GraphPointer graph, char vertex) {
    // debugging purposes
    // printf("Graph has vertex %c\n", vertex);

    int index = ((int) vertex - (int) 'A');

    // debugging purposes
    // printf("Index of %c: %d\n", vertex, index);

    return index >= graph->n ? -1 : index;
}

int hasEdge(GraphPointer graph, char from, char to) {
    int fromVertex = hasVertex(graph, from);
    int toVertex = hasVertex(graph, to);
    if (fromVertex == -1 || toVertex == -1) {
        return -1;
    }

    GraphNodePointer current = graph->adjacency_list[fromVertex].next;
    while (current != NULL) {
        if (current->vertex == to) {
            return current->weight; 
        }
        current = current->next;
    }

    return -1;
}

int addEdge(GraphPointer graph, char from, char to, int weight) {
    int fromVertex = hasVertex(graph, from);
    int toVertex = hasVertex(graph, to);
    if (fromVertex == -1 || toVertex == -1) {
        return -1;
    }

    if (hasEdge(graph, from, to) >= 0) {
        return -1;
    }

    // insert last becoz ez
    // this should works :V
    GraphNode *newGraphNode = malloc(sizeof(GraphNode));
    newGraphNode->vertex = to;
    newGraphNode->next = NULL;
    newGraphNode->weight = weight;
    GraphNodePointer current = &(graph->adjacency_list[fromVertex]);
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newGraphNode;

    return 1;
}

int getIndexOfVertex(char vertex) {
    return (int) vertex - (int) 'A';
}


char getVertexOfIndex(int index) {
    return (char) (index + (int) 'A');
}

GraphNode getVertexFromGraph(GraphPointer graph, char vertex) {
    int found = 0;
    for (int i = 0; i < graph->n; i++) {
        if (graph->adjacency_list[i].vertex == vertex) {
            return graph->adjacency_list[i];
        }
    }
    GraphNode dummy;
    dummy.vertex = NO_VERTEX;
    dummy.next = NULL;
    dummy.weight = -1;
    return dummy;
}

void resetArray(int *array, int n, int value) {
    for (int i = 0; i < n; i++) {
        array[i] = value;
    }
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
    newMinHeap->minHeap = malloc(sizeof(MinHeap) * newMinHeap->size);
    for (int i = 0; i < newMinHeap->size; i++) {
        newMinHeap->minHeap[i].distance = INT_MAX;
        newMinHeap->minHeap[i].vertex = -1;
    }
    return newMinHeap;
}

void resetMinHeap(MinHeap *minHeap) {
    // build this other helper function
    minHeap->count = 0;
}

void destroyMinHeap(MinHeap **minHeap) {
    free((*minHeap)->minHeap);
    free((*minHeap));
    (*minHeap) = NULL;
    return;
}

void printMinHeapAsArray(MinHeap *minHeap) {
    for (int i = 0; i < minHeap->count; i++) {
        if (minHeap->minHeap[i].vertex != -1) {
            // replace + with ,
            printf("Vertex: %d Distance: %d ", minHeap->minHeap[i].vertex, minHeap->minHeap[i].distance);
        } else {
            printf("(empty) ");
        }
    }
    printf("\n");
}

int insertMinHeap(MinHeap *minHeap, char vertex, int distance) {
    if (isFull(minHeap)) {
        return 0;
    }
    minHeap->minHeap[minHeap->count].vertex = vertex;
    minHeap->minHeap[minHeap->count].distance = distance;
    heapifyUp(minHeap, minHeap->count);

    minHeap->count++;

    return 1;
}

HeapNode extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap)) {
        printf("Minheap is empty! Failed to extract...\n");
        HeapNode dummy;
        dummy.vertex = -1;
        dummy.distance = INT_MAX;
        return dummy;
    }
    HeapNode minimumValue = minHeap->minHeap[0];
    HeapNode lastElement = minHeap->minHeap[minHeap->count - 1];
    minHeap->minHeap[0] = lastElement;
    minHeap->count -= 1;
    heapifyDown(minHeap, 0);

    return minimumValue;
}

// heapify functions
void heapifyUp(MinHeap *minHeap, int index) {
    // start at index (ideally the last element inserted) = count - 1
    // compare element at index vs parent element
    int childIndex = index;
    int parentIndex = getParentIndex(index);

    // while we still have a valid parent index...
    while (parentIndex >= 0) {
        // check if we need to swap:
        HeapNode parent = minHeap->minHeap[parentIndex];
        HeapNode child = minHeap->minHeap[childIndex];
    
        if (child.distance < parent.distance) {
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
}

void heapifyDown(MinHeap *minHeap, int index) {
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
            HeapNode leftChild = minHeap->minHeap[leftChildIndex];
            HeapNode rightChild = minHeap->minHeap[rightChildIndex];

            if (leftChild.distance < rightChild.distance) {
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
        HeapNode child = minHeap->minHeap[childIndex];
        HeapNode parent = minHeap->minHeap[parentIndex];
        // if the current node's value > smaller child, 
        if (parent.distance > child.distance) {
            // perform swap
            HeapNode temp = child;
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

// other functions
int isEmpty(MinHeap *minHeap) {
    return minHeap->count == 0 ? 1 : 0;
}

int isFull(MinHeap *minHeap) {
    return minHeap->count >= minHeap->size - 1 ? 1 : 0;
}

// actual algorithms
void dijkstra_explore(GraphPointer graph, char start, int *distances, int *parent, MinHeap *minheap) {
    // initialize distance -> infinity
    // parent as -1 for all nodes
    // distance to starting node as 0

    distances[(int) start - 'A'] = 0;

    insertMinHeap(minheap, start, 0);

    while (!isEmpty(minheap)) {
        HeapNode min = extractMin(minheap);

        if (min.distance > distances[(int) min.vertex - 'A']) {
            continue;
        }

        GraphNode currentVertex = getVertexFromGraph(graph, min.vertex);
        GraphNode *currentNeighbor = currentVertex.next;

        while (currentNeighbor != NULL) {
            int tempDistance = distances[(int) min.vertex - 'A'] + currentNeighbor->weight;

            if (tempDistance <= distances[(int) currentNeighbor->vertex - 'A']) {
                distances[(int) currentNeighbor->vertex - 'A'] = tempDistance;
                parent[(int) currentNeighbor->vertex - 'A'] = (int) min.vertex - 'A';
                insertMinHeap(minheap, (int) currentNeighbor->vertex, tempDistance);
            }

            currentNeighbor = currentNeighbor->next;
        }
    }

    return;
}

int dijkstra_target(GraphPointer graph, char start, char target, int *distances, int *parent, MinHeap *minheap) {
    // initialize helper arrays (done in main)
    // initialize distance to start as 0
    // insert start to minheap

    distances[(int) start - 'A'] = 0;

    insertMinHeap(minheap, start, 0);

    while (!isEmpty(minheap)) {
        // extract min from minheap
        HeapNode min = extractMin(minheap);

        // if we hit the target, we break :V
        if (min.vertex == target) {
            printf("TARGET FOUND!!!\n");
            break;
        }

        // if the extracted distance is greater than the current minimum distance,
        // we can disregard it (continue)
        if (min.distance > distances[(int) min.vertex - 'A']) {
            continue;
        }

        // loop through each neighbor
        GraphNode currentVertex = getVertexFromGraph(graph, min.vertex);
        GraphNode *currentNeighbor = currentVertex.next;

        while (currentNeighbor != NULL) {
            int tempDistance = distances[(int) min.vertex - 'A'] + currentNeighbor->weight;

            if (tempDistance <= distances[(int) currentNeighbor->vertex - 'A']) {
                distances[(int) currentNeighbor->vertex - 'A'] = tempDistance;
                parent[(int) currentNeighbor->vertex - 'A'] = (int) min.vertex - 'A';
                insertMinHeap(minheap, (int) currentNeighbor->vertex, tempDistance);
            }
            currentNeighbor = currentNeighbor->next;
        }
    }

    return 0;
}

// path printer function
void printPath(char start, char target, int *parent) {
    if (start == target) {
        printf("%c", start);
        return;
    }
    printPath(start, (char) parent[(int) target - 'A'], parent);
    printf(" -> %c", target);
}

// distance printer function
void printDistances(char start, int *distances, int n) {
    printf("Printing distances from: %c\n", start);
    printf("Node\t\tDistance from %c\n", start);
    for (int i = 0; i < n; i++) {
        if (distances[i] == INT_MAX) {
            printf("%c\t\t(infinity)",'A' + i);
        } else {
            printf("%c\t\t%d", 'A' + i, distances[i]);
        }
        printf("\n");
    }
}

// print weight given a path 
void printWeightGivenPath(GraphPointer graph, char start, char target, int *parent) {
    if (parent[(int) target - 'A'] == -1 && target != start) {
        printf("Total Weight: (infinity)\n");
        return;
    }

    int totalWeight = 0;
    char currentVertex = target;

    while (currentVertex != start) {
        char previous = 'A' + parent[(int) currentVertex - 'A'];
        GraphNode previousNode = getVertexFromGraph(graph, previous);
        GraphNode *currentNeighbor = previousNode.next;
        int currentEdgeWeight = -1;

        while (currentNeighbor != NULL) {
            if (currentNeighbor->vertex == currentVertex) {
                currentEdgeWeight = currentNeighbor->weight;
                break;
            }
            currentNeighbor = currentNeighbor->next;
        }

        if (currentEdgeWeight == -1) {
            totalWeight = -1;
            break;
        }
        // do stuff here. increment total weight
        totalWeight += currentEdgeWeight;
        currentVertex = previous;
    }

    if (totalWeight == -1) {
        printf("Total Weight: (infinity)\n");
        return;
    } else {  
        printf("Total Weight: %d\n", totalWeight);
    }
}
