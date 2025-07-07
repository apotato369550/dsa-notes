#include <stdio.h>
#include <stdlib.h>

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

// stuff i need to make:
// hasVertex
int hasVertex(GraphPointer graph, int vertex);

// isVisited
int isVisited(int vertex, int *visited);

// resetVisited
void resetVisited(int *visited, int n);

// dfs functions:
// DFS_explore
void DFS_explore(GraphPointer graph, char current, int *visited);

// DFS_target
int DFS_target(GraphPointer graph, char current, char target, int *visited, int *parent);

// other functions
// printPath
void printPath(char start, char target, int *parent);

int main() {
    Graph *graph = createGraph(10);

    if (graph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }

    addEdge(graph, 0, 1, 1); 
    addEdge(graph, 1, 0, 1);

    addEdge(graph, 0, 2, 1); 
    addEdge(graph, 2, 0, 1);

    addEdge(graph, 1, 3, 1); 
    addEdge(graph, 3, 1, 1);

    addEdge(graph, 2, 4, 1); 
    addEdge(graph, 4, 2, 1);

    addEdge(graph, 3, 5, 1); 
    addEdge(graph, 5, 3, 1);

    addEdge(graph, 4, 6, 1); 
    addEdge(graph, 6, 4, 1);

    addEdge(graph, 5, 6, 1);
    addEdge(graph, 6, 5, 1);

    addEdge(graph, 6, 7, 1); 
    addEdge(graph, 7, 6, 1);

    addEdge(graph, 8, 9, 1);
    addEdge(graph, 9, 8, 1);

    int *visited = calloc(graph->n, sizeof(int));
    int *parent = calloc(graph->n, sizeof(int));

    DFS_explore(graph, 0, visited);

    resetVisited(visited, graph->n);

    // should find path

    
    if (DFS_target(graph, 0, 7, visited, parent)) {
        printf("A path was found from A to H!!!\n");
        printPath(0, 7, parent);
    } else {
        printf("Could not find path from A to H:((\n");
    } 
    resetVisited(visited, graph->n);

    // should report not reachable
    if (DFS_target(graph, 0, 8, visited, parent)) {
        printf("A path was found from A to I!!!\n");
    } else {
        printf("Could not find path from A to I:((\n");
    } 
    resetVisited(visited, graph->n);

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
void DFS_explore(GraphPointer graph, char current, int *visited) {
    if (isVisited(current, visited)) {
        // printf("Vertex %d has already been visited...\n", current);
        return;
    }
    visited[current] = 1;
    if (!hasVertex(graph, current)) {
        printf("Vertex %d not found in graph:(( Returning...\n", current);
        return;
    }
    printf("Visiting vertex %d\n", current);
    for (int i = 0; i < graph->n; i++) {
        if (i == current || graph->edges[i] == 0) {
            continue;
        }
        DFS_explore(graph, i, visited);
    }

}

// DFS_target
int DFS_target(GraphPointer graph, char current, char target, int *visited, int *parent) {
    if (current == target) {
        return 1;
    }

    // stopped here
    if (!hasVertex(graph, current)) {
        return 0;
    }

    if (isVisited(current, visited)) {
        return 0;
    }
 
    visited[current] = 1;

    for (int i = 0; i < graph->n; i++) {
        if (i == current || graph->edges[i] == 0) {
            continue;
        }
        if (!visited[i]) {
            parent[i] = current;
            if (DFS_target(graph, i, target, visited, parent)) {
                return 1;
            }
        }
    }
}


// printPath
void printPath(char start, char target, int *parent) {
    if (start == target) {
        printf("%d", start);
        return;
    }   
    printPath(start, parent[target], parent);
    printf(" -> %d", target);
}