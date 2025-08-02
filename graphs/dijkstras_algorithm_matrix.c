#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Graph {
    int n;
    int **edges;
} Graph, *GraphPointer;

typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

// we need a minheap to store the lowest value
typedef struct {
    HeapNode *minHeap;
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
void resetMinHeap(MinHeap *minHeap);
void destroyMinHeap(MinHeap **minHeap);
void printMinHeapAsArray(MinHeap *minHeap);

// minheap helper functions

// insertion, extraction, and peeking
int insertMinHeap(MinHeap *minHeap, int vertex, int distance);
HeapNode extractMin(MinHeap *minHeap);
HeapNode peekMin(MinHeap *minHeap);

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
void dijkstra_explore(GraphPointer graph, int start, int *distances, int *parent, MinHeap *minheap);
int dijkstra_target(GraphPointer graph, int start, int target, int *distances, int *parent, MinHeap *minheap);

// path printer function
void printPath(int start, int target, int *parent);

// distance printer function
void printDistances(int start, int *distances, int n);

// print weight given a path 
void printWeightGivenPath(GraphPointer graph, int start, int target, int *parent);

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

    // perform dijkstra's here
    int *distances = malloc(sizeof(int) * graph->n);
    int *parent = malloc(sizeof(int) * graph->n);
    MinHeap *minheap = createMinHeap(graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);

    printGraph(graph);

    // dijkstra explore

    // 0
    dijkstra_explore(graph, 0, distances, parent, minheap);
    printDistances(0, distances, graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // 14
    dijkstra_explore(graph, 14, distances, parent, minheap);
    printDistances(14, distances, graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // 18
    dijkstra_explore(graph, 18, distances, parent, minheap);
    printDistances(18, distances, graph->n);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // 0 - 9
    dijkstra_target(graph, 0, 9, distances, parent, minheap);
    printPath(0, 9, parent);
    printWeightGivenPath(graph, 0, 9, parent);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // 10 - 14
    
    dijkstra_target(graph, 10, 14, distances, parent, minheap);
    printPath(10, 14, parent);
    printWeightGivenPath(graph, 10, 14, parent);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);

    // 15 - 19
    dijkstra_target(graph, 15, 19, distances, parent, minheap);
    printPath(15, 19, parent);
    printWeightGivenPath(graph, 15, 19, parent);

    resetArray(distances, graph->n, INT_MAX);
    resetArray(parent, graph->n, -1);
    resetMinHeap(minheap);


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

// minheap helper functions

// insertion, extraction, and peeking
int insertMinHeap(MinHeap *minHeap, int vertex, int distance) {
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

HeapNode peekMin(MinHeap *minHeap) {
    if (isEmpty(minHeap)) {
        printf("Minheap is empty! Failed to peek...\n");
        HeapNode dummy;
        dummy.vertex = -1;
        dummy.distance = INT_MAX;
        return dummy;
    }
    return minHeap->minHeap[0];
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



void dijkstra_explore(GraphPointer graph, int start, int distances[], int parent[], MinHeap *minheap) {
    // initialize:
    // distance as infinity for all nodes
    // parent as -1 for all nodes
    // distance to starting node as 0 for all nodes except start
    // (done outside of function :V)

    distances[start] = 0;

    // push start into minheap/minheap
    insertMinHeap(minheap, start, 0);

    // while the minheap is not empty:
    while (!isEmpty(minheap)) {
        // extract min (distance and vertex pair)
        HeapNode min = extractMin(minheap);
        // if min.current_distance > distance[current], continue [restart the loop and continue to extract min]
        if (min.distance > distances[min.vertex]) {
            continue;
        }

        // for each neighbor of current,
        for (int i = 0; i < graph->n; i++) {
            // if there is an edge:
            if (graph->edges[min.vertex][i] != 0) {
                // temp = dist[current] + matrix[current][destination] 
                int tempDistance = distances[min.vertex] + graph->edges[min.vertex][i];

                // if the current (temp) distance is better than the distance we've found so far, 
                // update distances and parent array
                if (tempDistance < distances[i]) {
                    // distances[destination] = temp
                    distances[i] = tempDistance;
                    // parent[destination] = current
                    parent[i] = min.vertex;
                    // push (temp, destination) to minheap
                    insertMinHeap(minheap, i, tempDistance);
                }
            }
        }
    }

    return;
}

int dijkstra_target(GraphPointer graph, int start, int target, int *distances, int *parent, MinHeap *minheap) {
    // logic fordiswan

    // initialize:
    // distance as infinity for all nodes
    // parent as -1 for all nodes
    // distance to starting node as 0 for all nodes except start
    // (done outside of function :V)

    // use minheap passed as argument from main
    // add start to minheap

    distances[start] = 0;

    // push start into minheap/minheap
    insertMinHeap(minheap, start, 0);

    // while the minheap is not empty:
    while (!isEmpty(minheap)) {
        // pop/extract min from minheap
        HeapNode min = extractMin(minheap);
        // if the vertex is the target, break

        if (min.vertex == target) {
            break;
        }

        // if the current distance (extracted) is greater than 
        // the distance from start to that vertex distances[u]
        // continue
        if (min.distance > distances[min.vertex]) {
            continue;
        }

        // loop through from i to n - 1 (number of vertices - 1)
        // basically loop through each neighbor
        for (int i = 0; i < graph->n; i++) {
            // if graph[current][i] != 0
            if (graph->edges[min.vertex][i] != 0) {
                // get temp distance 
                // distance = distances[current] + matrix[current][i]
                // or -> distance from start to that vertex + distance from current vertex to that vertex
                int tempDistance = distances[min.vertex] + graph->edges[min.vertex][i];
                // if temp < distances[destination]
                if (tempDistance < distances[i]) {
                    // distances[destination] = temp
                    distances[i] = tempDistance;
                    // parent[destination] = current
                    parent[i] = min.vertex;
                    // add to minheap: temp distance and neighbor/destination vertex
                    insertMinHeap(minheap, i, tempDistance);
                }
            }
        }
                
    }

    // return calculated distance to target from starting vertex after running through dijkstras
    return distances[target];
}

void printPath(int start, int target, int *parent) {
    if (start == target) {
        printf("%d", start);
        return;
    }   
    printPath(start, parent[target], parent);
    printf(" -> %d", target);
}

void printDistances(int start, int *distances, int n) {
    printf("Printing distances from: %d\n", start);
    printf("Node\t\tDistance from %d\n", start);
    for (int i = 0; i < n; i++) {
        if (distances[i] == INT_MAX) {
            printf("%d\t\t(infinity)", i);
        } else {
            printf("%d\t\t%d", i, distances[i]);
        }
        printf("\n");
    }
}

void printWeightGivenPath(GraphPointer graph, int start, int target, int *parent) {
    if (parent[target] == -1 && target != start) {
        printf("Total Weight: (infinity)\n");
        return;
    }

    int totalWeight = 0;
    int currentVertex = target;

    // go backwards
    while (currentVertex != start) {
        int previous = parent[currentVertex];
        int currentEdgeWeight = graph->edges[previous][currentVertex];
        totalWeight += currentEdgeWeight;
        currentVertex = previous;
    }

    printf("Total Weight: %d\n", totalWeight);
}