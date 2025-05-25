#include <stdio.h>

typedef struct Graph {
    int n;
    int **edges;
} Graph, *GraphPointer;

GraphPointer createGraph(int n);
void destroyGraph(GraphPointer graph);
void printGraph(Graph graph);

int main() {


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
void printGraph(Graph graph) {
    printf("----- START OF GRAPH -----\n");
    for (int i = 0; i < graph.n; i++) {
        for (int j = 0; j < graph.n; j++) {
            printf("%d ", graph.edges[i][j]);
        }
        printf("\n");
    }
    printf("----- END OF GRAPH -----\n")
}