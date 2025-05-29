#include <stdio.h>
#include <stdlib.h>

// declare structs for graph, and graphnode

typedef struct GraphNode {
    char vertex;
    int weight;
    struct GraphNode *next;
} GraphNode, *GraphNodePointer;

typedef struct Graph {
    int n;
    GraphNodePointer adjacency_list;
} Graph, *GraphPointer;

GraphPointer createGraph(int n);
int hasVertex(GraphPointer graph, char vertex);
int hasEdge(GraphPointer graph, char from, char to);
int addEdge(GraphPointer graph, char from, char to);
int removeEdge(GraphPointer graph, char from, char to);
void printGraph(GraphPointer graph);
int destroyGraph(GraphPointer graph);

int main() {
    Graph *graph = createGraph(6);

    if (graph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }

    printGraph(graph);

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

int hasVertex(GraphPointer graph, char vertex) {
    for (int i = 0; i < graph->n; i++) {
        if (graph->adjacency_list[i].vertex == vertex) {
            return i;
        }
    }
    return -1;
}

int hasEdge(GraphPointer graph, char from, char to) {
    int fromVertex = hasVertex(graph, from);
    int toVertex = hasVertex(graph, to);
    if (fromVertex == -1 || toVertex == -1) {
        return 0;
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

int addEdge(GraphPointer graph, char from, char to) {

    return 1;
}
int removeEdge(GraphPointer graph, char from, char to) {
    return 1;
}

void printGraph(GraphPointer graph) {
    printf("----- START OF GRAPH -----\n");
    for (int i = 0; i < graph->n; i++) {
        printf("Vertex %c: ", graph->adjacency_list[i].vertex);

        GraphNodePointer current = graph->adjacency_list[i].next;
        while (current != NULL) {
            printf("%c (%d)", current->vertex, current->weight);
            current = current->next;
        }

        printf("\n");
    }
    printf("----- END OF GRAPH -----\n");
    return;
}

int destroyGraph(GraphPointer graph) {
    free(graph->adjacency_list);
    free(graph);
}