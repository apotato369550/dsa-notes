#ifndef GRAPH
#define GRAPH

#define MAX_GRAPH_SIZE 13

typedef int MatrixGraph[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];

typedef struct {
    char vertex;
    int weight;
} GraphNode;

typedef GraphNode ListGraph[MAX_GRAPH_SIZE];


#endif