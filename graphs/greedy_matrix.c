#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Graph {
    int n;
    int **edges;
} Graph, *GraphPointer;

//  pre-built stuff
GraphPointer createGraph(int n);
void destroyGraph(GraphPointer graph);
void printGraph(GraphPointer graph);
int hasEdge(GraphPointer graph, int from, int to);
int addEdge(GraphPointer graph, int from, int to, int weight);
int removeEdge(GraphPointer graph, int from, int to);

// hasVertex
int hasVertex(GraphPointer graph, int vertex);

// isVisited
int isVisited(int vertex, int *visited);

// resetVisited
void resetVisited(int *visited, int n);

// complete and sparse graph maker functions 

void createCompleteEdges(GraphPointer graph);
void createDenseEdges(GraphPointer graph);

// create hamiltonian cycle using greedy function
void createHamiltonianCycle(GraphPointer graph, int start, int *visited);

int main () {
    Graph *completeGraph = createGraph(10);

    if (completeGraph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }

    Graph *denseGraph = createGraph(10);

    if (denseGraph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }

    createCompleteEdges(completeGraph);
    createDenseEdges(denseGraph);

    int *visited = calloc(completeGraph->n, sizeof(int));
    resetVisited(visited, completeGraph->n);

    printf("Printing Complete Graph: \n\n");
    printGraph(completeGraph);

    printf("Printing Dense Graph: \n\n");
    printGraph(denseGraph);

    createHamiltonianCycle(completeGraph, 0, visited);
    resetVisited(visited, completeGraph->n);
    createHamiltonianCycle(denseGraph, 0, visited);

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
            if (graph->edges[from][to] == INT_MAX) {
                printf("inf ");
            }
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

// stuff i need to make:
// hasVertex
int hasVertex(GraphPointer graph, int vertex) {
    return vertex >= graph->n ? 0 : 1;
}

// isVisited
int isVisited(int vertex, int *visited) {
    return visited[vertex];
}

// resetVisited
void resetVisited(int *visited, int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}


void createCompleteEdges(GraphPointer graph) {
    for (int i = 0; i < graph->n; i++) {
        for (int j = i + 1; j < graph->n; j++) {
            int weight = rand() % 9 + 1;
            addEdge(graph, i, j, weight);
            addEdge(graph, j, i, weight);
        }
    }
}

void createDenseEdges(GraphPointer graph) {
    // define density as the fraction of max edges
    double density = 0.75; 
    int edgeCount = (int)(density * (graph->n * (graph->n - 1)) / 2);

    // while the number of edges currently
    // added is less than edgeCount
    int addedEdges = 0;
    while (addedEdges < edgeCount) {
        // create a to-edge and from-edge
        int from = rand() % graph->n;
        int to = rand() % graph->n;

        // if they're the same, we skip it
        // since it's just a loop :V
        if (from == to) {   
            continue;
        }

        if (!hasEdge(graph, from, to) && !hasEdge(graph, to, from)) {
            int weight = rand() % 9 + 1;
            addEdge(graph, from, to, weight);
            addEdge(graph, to, from, weight);
        }
        addedEdges += 1;
    }
    
    for (int i = 0; i < graph->n; i++) {
        for (int j = i + 1; j < graph->n; j++) {
            if (graph->edges[i][j] == 0) {
                graph->edges[i][j] = INT_MAX;
            }
        }
    }
}

void createHamiltonianCycle(GraphPointer graph, int start, int *visited) {
    // so what we can do here is, 
    // we can loop through n times, then after looping, 
    int currentVertex = start;
    int totalWeight = 0;

    // mark start as visited
    visited[start] = 1;
    printf("%d->", start);
    // since start is visited, we can loop n - 1 times instead
    for (int i = 0; i < graph->n - 1; i++) {
        // let's try mapping out the logic for getting the next vertex,
        // then if possible, delegate the responsibility to a helper function
        int lowestWeightEdgeIndex = -1;
        int lowestWeightEdgeWeight = INT_MAX;

        // the code segment below finds the least costly edge: its index and its weight
        for (int j = 0; j < graph->n; j++) {
            // if it's an edge that's been visited, continue
            if (visited[j]) {
                continue;
            }
            // otherwise, it hasn't been visited and is the candidate for being the smallest weight edge
            // if it's lower than the ones we've found, 
            if (graph->edges[i][j] < lowestWeightEdgeWeight) {
                // reassign the variables chuchu
                lowestWeightEdgeIndex = j;
                lowestWeightEdgeWeight = graph->edges[i][j];
            }
        }

        // do stuff with index and weights and shit
        printf("%d->", lowestWeightEdgeIndex);
        visited[lowestWeightEdgeIndex] = 1;
        totalWeight += lowestWeightEdgeWeight;

        // we reassign currentvertex to be the next vertex
        currentVertex = lowestWeightEdgeIndex;
    }
    // go from current vertex to start vertex, account for weight, then return weight
    // for now, let's leave cycle storage and printing some other time. right now let's focus on getting the logic down
    totalWeight += graph->edges[currentVertex][start];
    printf("%d\n", start);

    printf("Total cycle weight: %d", totalWeight);
}