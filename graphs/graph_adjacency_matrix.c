#include <stdio.h>

typedef struct Graph {
    struct Graph **graph;
} Graph, *GraphPointer;

Graph *createGraph(int n);
void destroyGraph(GraphPointer graph);
void printGraph(Graph graph);

int main() {


    return 0;
}

Graph *createGraph(int n);
void destroyGraph(GraphPointer graph);
void printGraph(Graph graph);