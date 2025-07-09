#include <stdio.h>
#include <stdlib.h>

#define NO_VERTEX '*'

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
int addEdge(GraphPointer graph, char from, char to, int weight);
int isVisited(char vertex, int *visited);
int getIndexOfVertex(char vertex);
char getVertexOfIndex(int index);
void printGraph(GraphPointer graph);
GraphNode getVertexFromGraph(GraphPointer graph, char vertex);
void resetArray(int *visited, int n);
int destroyGraph(GraphPointer graph);

void BFS_explore(GraphPointer graph, char current, int *visited);
int BFS_target(GraphPointer graph, char current, char target, int *visited, int *parent);

void printPath(char start, char target, int *parent);

/*
        A
       / \
      B   C
     /     \
    D       E
   / \     /
  F   G - H
         /
        I

J - K     (Disconnected component)
|
L
|
M

*/


int main() {
    Graph *graph = createGraph(15);

    if (graph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }

    addEdge(graph, 'A', 'B', 1); addEdge(graph, 'B', 'A', 1);
    addEdge(graph, 'A', 'C', 1); addEdge(graph, 'C', 'A', 1);

    addEdge(graph, 'B', 'D', 1); addEdge(graph, 'D', 'B', 1);
    addEdge(graph, 'C', 'E', 1); addEdge(graph, 'E', 'C', 1);

    addEdge(graph, 'D', 'F', 1); addEdge(graph, 'F', 'D', 1);
    addEdge(graph, 'D', 'G', 1); addEdge(graph, 'G', 'D', 1);

    addEdge(graph, 'E', 'H', 1); addEdge(graph, 'H', 'E', 1);
    addEdge(graph, 'G', 'H', 1); addEdge(graph, 'H', 'G', 1);
    addEdge(graph, 'H', 'I', 1); addEdge(graph, 'I', 'H', 1);

    // Disconnected component
    addEdge(graph, 'J', 'K', 1); addEdge(graph, 'K', 'J', 1);
    addEdge(graph, 'J', 'L', 1); addEdge(graph, 'L', 'J', 1);
    addEdge(graph, 'L', 'M', 1); addEdge(graph, 'M', 'L', 1);


    int *visited = calloc(graph->n, sizeof(int));
    int *parent = calloc(graph->n, sizeof(int));

    DFS_explore(graph, 'A', visited);

    resetArray(visited, graph->n);
    resetArray(parent, graph->n);

    destroyGraph(graph);
    free(visited);
    free(parent);

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
    // debugging purposes
    // printf("Graph has vertex %c\n", vertex);

    int index = ((int) vertex - (int) 'A');

    // debugging purposes
    // printf("Index of %c: %d\n", vertex, index);

    return index >= graph->n ? -1 : index;
}

int hasEdge(GraphPointer graph, char from, char to) {
    int fromVertex = hasVertex(graph, from);
    int toVertex = hasVertex(graph, to);
    if (fromVertex == -1 || toVertex == -1) {
        return -1;
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

int addEdge(GraphPointer graph, char from, char to, int weight) {
    int fromVertex = hasVertex(graph, from);
    int toVertex = hasVertex(graph, to);
    if (fromVertex == -1 || toVertex == -1) {
        return -1;
    }

    if (hasEdge(graph, from, to) >= 0) {
        return -1;
    }

    // insert last becoz ez
    // this should works :V
    GraphNode *newGraphNode = malloc(sizeof(GraphNode));
    newGraphNode->vertex = to;
    newGraphNode->next = NULL;
    newGraphNode->weight = weight;
    GraphNodePointer current = &(graph->adjacency_list[fromVertex]);
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newGraphNode;

    return 1;
}

int isVisited(char vertex, int *visited) {
    // omg im so dumb.
    // i checked if any was visited instead of just the index T_T
    int index = getIndexOfVertex(vertex);
    return visited[index];
}

int getIndexOfVertex(char vertex) {
    return (int) vertex - (int) 'A';
}

char getVertexOfIndex(int index) {
    return (char) (index + (int) 'A');
}

void printGraph(GraphPointer graph) {
    printf("----- START OF GRAPH -----\n");
    for (int i = 0; i < graph->n; i++) {
        printf("Vertex %c: ", graph->adjacency_list[i].vertex);

        GraphNodePointer current = graph->adjacency_list[i].next;
        while (current != NULL) {
            printf("%c (%d)", current->vertex, current->weight);
            if (current->next != NULL) {
                printf(" -> ");
            }
            current = current->next;
        }

        printf("\n");
    }
    printf("----- END OF GRAPH -----\n");
    return;
}

GraphNode getVertexFromGraph(GraphPointer graph, char vertex) {
    int found = 0;
    for (int i = 0; i < graph->n; i++) {
        if (graph->adjacency_list[i].vertex == vertex) {
            return graph->adjacency_list[i];
        }
    }
    GraphNode dummy;
    dummy.vertex = NO_VERTEX;
    dummy.next = NULL;
    dummy.weight = -1;
    return dummy;
}

void resetArray(int *visited, int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

int destroyGraph(GraphPointer graph) {
    free(graph->adjacency_list);
    free(graph);
}


void BFS_explore(GraphPointer graph, char current, int *visited) {
    // create an empty queue
    // mark start as visited
    // add start to queue
    // while queue is not empty
        // dequeue an item
        // process said item
        // for each neighbor:
            // enqueue its neighbors
            // continue logic here :V

    return;
}

int BFS_target(GraphPointer graph, char current, char target, int *visited, int *parent) {
    return 0;
}


void printPath(char start, char target, int *parent) {
    if (start == target) {
        printf("%c", start);
        return;
    }
    printPath(start, getVertexOfIndex(parent[getIndexOfVertex(target)]), parent);
    printf(" -> %c", target);
}
