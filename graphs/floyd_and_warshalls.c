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

// create floyd and warshalls function
void floydAndWarshalls(GraphPointer graph);

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

    floydAndWarshalls(completeGraph);
    floydAndWarshalls(denseGraph);

    printf("Printing Complete Graph after Floyd and Warshall's: \n\n");
    printGraph(completeGraph);

    printf("Printing Dense Graph after Floyd and Warshall's: \n\n");
    printGraph(denseGraph);

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
            } else {
                printf("%d ", graph->edges[from][to]);
            }
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

void floydAndWarshalls(GraphPointer graph) {
    for (int k = 0; k < graph->n; k++) {
        for (int i = 0; i < graph->n; i++) {
            for (int j = 0; j < graph->n; j++) {
                // if any of the values are infinite, stop checking for this iteration
                if (graph->edges[i][k] == INT_MAX || graph->edges[k][j] == INT_MAX || graph->edges[i][j] == INT_MAX ) {
                    continue;
                }
                // check floyd-warshall condition
                if (graph->edges[i][k] + graph->edges[k][j] < graph->edges[i][j]) {
                    graph->edges[i][j] = graph->edges[i][k] + graph->edges[k][j];
                }
            }
        }
    }
}