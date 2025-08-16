#include <stdio.h>
#include <stdlib.h>

// declare structs for graph, and graphnode

typedef struct GraphNode {
    char vertex;
    int weight;
    struct GraphNode *next;
} GraphNode, *GraphNodePointer;

// i think adjacency list should be a double pointer...
// unless i can "magic" it in a way where it shouldn't have to be...
typedef struct Graph {
    int n;
    GraphNodePointer adjacency_list;
} Graph, *GraphPointer;

GraphPointer createGraph(int n);
int hasVertex(GraphPointer graph, char vertex);
int hasEdge(GraphPointer graph, char from, char to);
int addEdge(GraphPointer graph, char from, char to, int weight);
int removeEdge(GraphPointer graph, char from, char to);
void printGraph(GraphPointer graph);
int destroyGraph(GraphPointer graph);

int main() {
    Graph *graph = createGraph(6);

    if (graph == NULL) {
        printf("Failed to allocate memory...\n");
        return 1;
    }

    addEdge(graph, 'A', 'B', 10);
    addEdge(graph, 'B', 'A', 10);
    addEdge(graph, 'A', 'C', 20);
    addEdge(graph, 'A', 'D', 20);
    addEdge(graph, 'A', 'E', 20);
    addEdge(graph, 'B', 'C', 12);
    addEdge(graph, 'D', 'E', 2);

    printGraph(graph);

    hasEdge(graph, 'A', 'B');
    hasEdge(graph, 'A', 'E');
    hasEdge(graph, 'D', 'E');

    removeEdge(graph, 'A', 'B');
    removeEdge(graph, 'A', 'C');

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
        printf("An edge from %c to %c does not exist...\n", from, to);
        return -1;
    }

    GraphNodePointer current = graph->adjacency_list[fromVertex].next;
    while (current != NULL) {
        if (current->vertex == to) {
            printf("Graph has edge from %c to %c\n", from, to);
            return current->weight; 
        }
        current = current->next;
    }

    printf("An edge from %c to %c does not exist...\n", from, to);
    return -1;
}

// debug insertion
// i REALLY need to review my linked list basics :V
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
int removeEdge(GraphPointer graph, char from, char to) {
    int fromVertex = hasVertex(graph, from);
    int toVertex = hasVertex(graph, to);
    if (fromVertex == -1 || toVertex == -1) {
        printf("Vertex %c or %c does not exist...\n", from, to);
        return -1;
    }

    if (hasEdge(graph, from, to) == -1) {
        return -1;
    }
    GraphNodePointer current = &(graph->adjacency_list[fromVertex]);
    // we can assume that the edge exists within the ll thanks to hasEdge()
    while (current->next->vertex != to) {
        current = current->next;
    }

    GraphNodePointer temp = current->next;

    if (temp->next != NULL) {
        current->next = temp->next;
    }

    free(temp);

    // ok so time to derive the logic...
    // if it's in current->next, check if current->next->next exists
    // create tempt for current->next
    // link current with current->next->next
    // free temp
    // should be ok??
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

int destroyGraph(GraphPointer graph) {
    free(graph->adjacency_list);
    free(graph);
}