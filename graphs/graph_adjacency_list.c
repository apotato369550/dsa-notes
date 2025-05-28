#include <stdio.h>
#include <stdlib.h>

// declare structs for graph, and graphnode

typedef struct GraphNode {
    char vertex;
    int weight;
    struct GraphNode *next;
} GraphNode, *GraphNodePointer;

typedef struct Graph {
    GraphNodePointer adjacency_list;
} Graph, *GraphPointer;

GraphPointer createGraph(GraphPointer adjacency_list, int n);
int hasEdge(GraphPointer adjacency_list, char from, char to);
int addEdge(GraphPointer adjacency_list, char from, char to);
int removeEdge(GraphPointer adjacency_list, char from, char to);
void printGraph(GraphPointer adjacency_list);
int destroyGraph(GraphPointer adjacency_list);

int main() {
    

    return 0;
}