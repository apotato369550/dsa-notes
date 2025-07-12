#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int n;
    int **edges;
} Graph, *GraphPointer;

// re-implement queue to use indices instead of other stuff idk

//  pre-built stuff
GraphPointer createGraph(int n);
void destroyGraph(GraphPointer graph);
void printGraph(GraphPointer graph);
int hasEdge(GraphPointer graph, int from, int to);
int addEdge(GraphPointer graph, int from, int to, int weight);
int removeEdge(GraphPointer graph, int from, int to);

// stuff i need to make:
// hasVertex
int hasVertex(GraphPointer graph, int vertex);

// isVisited
int isVisited(int vertex, int *visited);

// resetVisited
void resetArray(int *array, int n);

// dfs functions:
// DFS_explore
// forgot to change current and target to int from char after transferring it from adj list implementation
void BFS_explore(GraphPointer graph, int current, int *visited);

// DFS_target
int BFS_target(GraphPointer graph, int current, int target, int *visited, int *parent);

// other functions
// printPath
void printPath(int start, int target, int *parent);

/*
        0
       / \
      1   2
     /     \
    3       4
   / \     /
  5   6 - 7
         /
        8

9 - 10     (Disconnected component)
|
11
|
12

*/
int main() {
    Graph *graph = createGraph(15);

    if (graph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }

    addEdge(graph, 0, 1, 1); addEdge(graph, 1, 0, 1);  // A-B
    addEdge(graph, 0, 2, 1); addEdge(graph, 2, 0, 1);  // A-C

    addEdge(graph, 1, 3, 1); addEdge(graph, 3, 1, 1);  // B-D
    addEdge(graph, 2, 4, 1); addEdge(graph, 4, 2, 1);  // C-E

    addEdge(graph, 3, 5, 1); addEdge(graph, 5, 3, 1);  // D-F
    addEdge(graph, 3, 6, 1); addEdge(graph, 6, 3, 1);  // D-G

    addEdge(graph, 4, 7, 1); addEdge(graph, 7, 4, 1);  // E-H
    addEdge(graph, 6, 7, 1); addEdge(graph, 7, 6, 1);  // G-H
    addEdge(graph, 7, 8, 1); addEdge(graph, 8, 7, 1);  // H-I

    // Disconnected component
    addEdge(graph, 9, 10, 1); addEdge(graph, 10, 9, 1);  // J-K
    addEdge(graph, 9, 11, 1); addEdge(graph, 11, 9, 1);  // J-L
    addEdge(graph, 11, 12, 1); addEdge(graph, 12, 11, 1);  // L-M


    int *visited = calloc(graph->n, sizeof(int));
    int *parent = calloc(graph->n, sizeof(int));

    printGraph(graph);

    DFS_explore(graph, 0, visited);

    resetArray(visited, graph->n);
    resetArray(visited, graph->n);

    destroyGraph(graph);
    free(visited);
    free(parent);

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

// stuff i need to make:
// hasVertex
int hasVertex(GraphPointer graph, int vertex) {
    return vertex >= graph->n ? 0 : 1;
}

void resetArray(int *array, int n) {
    for (int i = 0; i < n; i++) {
        array[i] = 0;
    }
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

// dfs functions:
// DFS_explore
void BFS_explore(GraphPointer graph, int current, int *visited) {

    return;

}

// DFS_target
int BFS_target(GraphPointer graph, int current, int target, int *visited, int *parent) {
    return 0;
}


// printPath
void printPath(int start, int target, int *parent) {
    if (start == target) {
        printf("%d", start);
        return;
    }   
    printPath(start, parent[target], parent);
    printf(" -> %d", target);
}