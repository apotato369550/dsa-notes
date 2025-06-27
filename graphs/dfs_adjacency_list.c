#include <stdio.h>


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
int addEdge(GraphPointer graph, char from, char to, int weight);
void printGraph(GraphPointer graph);
GraphNode *getVertexFromGraph(GraphPointer graph, char vertex);
int destroyGraph(GraphPointer graph);

void DFS_explore(GraphPointer graph, char current, int *visited);
void DFS_target(GraphPointer graph, char start, char target);

int main() {
    Graph *graph = createGraph(10);

    if (graph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }
    addEdge(graph, 'A', 'B', 1); 
    addEdge(graph, 'B', 'A', 1);

    addEdge(graph, 'A', 'C', 1); 
    addEdge(graph, 'C', 'A', 1);

    addEdge(graph, 'B', 'D', 1); 
    addEdge(graph, 'D', 'B', 1);

    addEdge(graph, 'C', 'E', 1); 
    addEdge(graph, 'E', 'C', 1);

    addEdge(graph, 'D', 'F', 1); 
    addEdge(graph, 'F', 'D', 1);

    addEdge(graph, 'E', 'G', 1); 
    addEdge(graph, 'G', 'E', 1);

    addEdge(graph, 'F', 'G', 1);
    addEdge(graph, 'G', 'F', 1);

    addEdge(graph, 'G', 'H', 1); 
    addEdge(graph, 'H', 'G', 1);

    addEdge(graph, 'I', 'J', 1);
    addEdge(graph, 'J', 'I', 1);

    int *visited = calloc(graph->n, sizeof(int));

    DFS_explore(graph, 'A', visited);

    DFS_target(graph->adjacency_list, 'A', 'H');   // should find path
    DFS_target(graph->adjacency_list, 'A', 'I');   // should report not reachable

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


int addEdge(GraphPointer graph, char from, char to, int weight) {
    int fromVertex = hasVertex(graph, from);
    int toVertex = hasVertex(graph, to);
    if (fromVertex == -1 || toVertex == -1) {
        printf("Vertex %c or %c does not exist...\n", from, to);
        return -1;
    }

    if (hasEdge(graph, from, to) >= 0) {
        printf("An edge already exists from %c to %c...\n", from, to);
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

GraphNode *getVertexFromGraph(GraphPointer graph, char vertex) {
    for (int i = 0; i < graph->n; i++) {
        // complete this...
        GraphNode *currentVertex = NULL;
    }
    return NULL;
}

int destroyGraph(GraphPointer graph) {
    free(graph->adjacency_list);
    free(graph);
}

void DFS_explore(GraphPointer graph, char current, int *visited) {
    int isVisited = 0;
    int currentIndexVisited = (int) current - (int) 'A';
    for (int i = 0; i < graph->n; i++) {
        if (visited[currentIndexVisited] == 1) {
            isVisited = 1;
            break;
        }
    }
    if (isVisited) {
        return;
    }
    visited[currentIndexVisited] = 1;
    // process
    printf("Visiting: %c\n", current);

    // we need a sort of search function to get the current graph's next
    GraphNode *currentVertex = getVertexFromGraph(graph, current);

    if (currentVertex == NULL) {
        printf("Vertex not found in graph:(( Returning...\n");
        return;
    }

    GraphNode *currentNeighbor = currentVertex->next;

    while (currentNeighbor != NULL) {
        // recurse and perform DFS explore
        DFS_explore(graph, currentNeighbor->vertex, visited);
        currentNeighbor = currentNeighbor->next;
    }

}

void DFS_target(GraphPointer graph, char start, char target) {
    return;
}