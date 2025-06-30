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
int isVisited(GraphPointer graph, char vertex, int *visited);
int getIndexOfVertex(char vertex);
char getVertexOfIndex(int index);
void printGraph(GraphPointer graph);
GraphNode getVertexFromGraph(GraphPointer graph, char vertex);
void resetVisited(int *visited, int n);
int destroyGraph(GraphPointer graph);

void DFS_explore(GraphPointer graph, char current, int *visited);
int DFS_target(GraphPointer graph, char current, char target, int *visited, int *parent);

void printPath(char start, char target, int *parent);

/*

    A
   / \
  B   C
 /     \
D       E
 \     /
   F - G
       |
       H

I - J  (Disconnected component)

*/


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
    int *parent = calloc(graph->n, sizeof(int));

    DFS_explore(graph, 'A', visited);

    resetVisited(visited, graph->n);

    // should find path
    if (DFS_target(graph, 'A', 'H', visited, parent)) {
        printf("A path was found from A to H!!!");
    } else {
        printf("Could not find path from A to H:((");
    } 
    resetVisited(visited, graph->n);

    // should report not reachable
    if (DFS_target(graph, 'A', 'I', visited, parent)) {
        printf("A path was found from A to I!!!");
    } else {
        printf("Could not find path from A to I:((");
    } 
    resetVisited(visited, graph->n);

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

int isVisited(GraphPointer graph, char vertex, int *visited) {
    for (int i = 0; i < graph->n; i++) {
        if (visited[(int) graph->adjacency_list[i].vertex - (int) 'A'] == 1) {
            return 1;
        }
    }
    return 0;   
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

void resetVisited(int *visited, int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

int destroyGraph(GraphPointer graph) {
    free(graph->adjacency_list);
    free(graph);
}

void DFS_explore(GraphPointer graph, char current, int *visited) {
    // check if current vertex is visited
    // if it is, return
    if (isVisited(graph, current, visited)) {
        return;
    }

    int currentVisitedIndex = getIndexOfVertex(current);
    // otherwise, update visited array
    visited[currentVisitedIndex] = 1;

    // process
    printf("Visiting: %c\n", current);

    // we need a sort of search function to get the current graph's next
    // so we get the current vertex from the graph
    GraphNode currentVertex = getVertexFromGraph(graph, current);

    // if the vertex does not exist, just return
    if (currentVertex.vertex == NO_VERTEX) {
        printf("Vertex not found in graph:(( Returning...\n");
        return;
    }

    // start interating through the vertex's neighbors
    GraphNode *currentNeighbor = currentVertex.next;

    while (currentNeighbor != NULL) {
        // recurse and perform DFS explore
        DFS_explore(graph, currentNeighbor->vertex, visited);
        currentNeighbor = currentNeighbor->next;
    }

}

int DFS_target(GraphPointer graph, char current, char target, int *visited, int *parent) {
    // if the current vertex is already visited, return false
    if (current == target) {
        return 1;
    }
    int currentVisitedIndex = getIndexOfVertex('current');
    // mark current as visited
    visited[currentVisitedIndex] = 1;

    // get current vertex
    GraphNode currentVertex = getVertexFromGraph(graph, current);
    
    // return if no vertex is found
    if (currentVertex.vertex == NO_VERTEX) {
        printf("Vertex not found in graph:(( Returning...\n");
        return 0;
    }

    // get current vertex's neighbors
    GraphNode *currentNeighbor = currentVertex.next;

    while (currentNeighbor != NULL) {
        int currentNeighborVertexIndex = getIndexOfVertex(currentNeighbor->vertex);
        if (visited[currentNeighborVertexIndex] == 0) {
            parent[currentNeighborVertexIndex] = currentNeighborVertexIndex;
            if (DFS_target(graph, currentNeighbor->vertex, target, visited, parent)) {
                return 1;
            }
        }
        currentNeighbor = currentNeighbor->next;
        // i think i should delegate the responsibility of finding if
        // current is in neighbor to another function
    }

    return 0;
}

void printPath(char start, char target, int *parent) {
    if (start == target) {
        printf("%c", start);
    }
    // printPath(start, index)
}
