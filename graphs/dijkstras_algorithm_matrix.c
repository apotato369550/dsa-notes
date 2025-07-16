#include <stdio.h>
#include <stdlib.h>

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
void resetArray(int *array, int n);

// minheap builder
MinHeap *createMinHeap(int size);
void destroyMinHeap(MinHeap **minHeap);
void printMinHeapAsArray(MinHeap *minHeap);

// minheap helper functions

// actual algorithms
void dijkstra_explore(GraphPointer graph, int start, int distances[], int parent[]);
int dijkstra_target(GraphPointer graph, int start, int target, int distances[], int parent[]);

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

int hasVertex(GraphPointer graph, int vertex);
int isVisited(int vertex, int *visited);
void resetArray(int *array, int n);


void dijkstra_explore(GraphPointer graph, int start, int distances[], int parent[]) {

    return;
}

int dijkstra_target(GraphPointer graph, int start, int target, int distances[], int parent[]) {

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