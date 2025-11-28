#include "adjacency_list.h"

// ============================================================================
// Basic Graph Operations
// ============================================================================

void initListGraph(AdjList *G, int numVertices, bool isDirected) {
    /* TODO: Initialize adjacency list graph
     * Algorithm:
     * 1. Allocate array of Edge pointers (size numVertices)
     * 2. Initialize each list to NULL
     * 3. Set G->numVertices and G->isDirected
     */
}

void addEdgeList(AdjList *G, Vertex u, Vertex v, int weight) {
    /* TODO: Add edge from u to v with given weight
     * Algorithm:
     * 1. Create new edge node for destination v with weight
     * 2. Insert at front of adjacency list for u
     * 3. If undirected, also add edge from v to u
     */
}

void removeEdgeList(AdjList *G, Vertex u, Vertex v) {
    /* TODO: Remove edge from u to v
     * Algorithm:
     * 1. Search adjacency list of u for edge to v
     * 2. Remove it from linked list
     * 3. If undirected, also remove edge from v to u
     */
}

bool hasEdgeList(AdjList *G, Vertex u, Vertex v) {
    /* TODO: Check if edge exists from u to v
     * Algorithm:
     * Traverse adjacency list of u looking for v
     * Return true if found, false otherwise
     * Time: O(degree(u))
     */
    return false;
}

int getEdgeWeightList(AdjList *G, Vertex u, Vertex v) {
    /* TODO: Return weight of edge from u to v
     * Algorithm:
     * Traverse adjacency list of u to find edge to v
     * Return its weight if found, INFINITY if not found
     */
    return INFINITY;
}

int countEdgesList(AdjList *G) {
    /* TODO: Count total number of edges
     * Algorithm:
     * For directed graph:
     *   Sum lengths of all adjacency lists
     * For undirected graph:
     *   Sum lengths of all lists and divide by 2
     *   (each edge appears twice)
     */
    return 0;
}

// ============================================================================
// ADT Operations from Aho Section 6.2
// ============================================================================

Edge firstList(AdjList *G, Vertex v) {
    /* TODO: Return first edge in adjacency list of v
     * Simply return G->adjList[v]
     * Returns NULL if v has no outgoing edges
     */
    return NULL;
}

Edge nextList(AdjList *G, Vertex v, Edge e) {
    /* TODO: Return next edge after e in adjacency list
     * Return e->next
     * Returns NULL if e is the last edge
     */
    return NULL;
}

Vertex vertexList(Vertex v, Edge e) {
    /* TODO: Return destination vertex of edge e
     * Return e->dest
     */
    return NIL;
}

// ============================================================================
// Edge Node Operations
// ============================================================================

EdgeNode* createEdgeNode(Vertex dest, int weight) {
    /* TODO: Create and initialize new edge node
     * Algorithm:
     * 1. Allocate memory for EdgeNode
     * 2. Set dest and weight
     * 3. Set next to NULL
     * 4. Return pointer
     */
    return NULL;
}

void insertEdgeFront(Edge *list, Vertex dest, int weight) {
    /* TODO: Insert new edge at front of list
     * Algorithm:
     * 1. Create new edge node
     * 2. Set new->next = *list
     * 3. Set *list = new
     */
}

void removeEdgeFromList(Edge *list, Vertex dest) {
    /* TODO: Remove edge to dest from list
     * Algorithm:
     * 1. Handle special case: removing first node
     * 2. Otherwise: find node before target
     * 3. Update pointers to skip target node
     * 4. Free target node
     */
}

EdgeNode* findEdgeInList(Edge list, Vertex dest) {
    /* TODO: Find edge to dest in list
     * Algorithm:
     * Traverse list comparing each node's dest with target
     * Return pointer to node if found, NULL otherwise
     */
    return NULL;
}

// ============================================================================
// Graph Properties
// ============================================================================

int degreeList(AdjList *G, Vertex v) {
    /* TODO: Count edges in adjacency list of v
     * Algorithm:
     * Traverse G->adjList[v] counting nodes
     */
    return 0;
}

int inDegreeList(AdjList *G, Vertex v) {
    /* TODO: Count incoming edges to v
     * Algorithm (inefficient for adjacency list!):
     * For each vertex u:
     *   Search adjacency list of u for edge to v
     *   If found, increment count
     * Time: O(|V| + |E|)
     * Note: This shows why adjacency list is poor for in-degree queries
     */
    return 0;
}

bool isEmptyList(AdjList *G) {
    /* TODO: Check if graph has no edges
     * Return true if all adjacency lists are NULL
     */
    return true;
}

bool isCompleteList(AdjList *G) {
    /* TODO: Check if graph is complete
     * For directed: each vertex should have n-1 outgoing edges
     * For undirected: each vertex should have n-1 edges
     * Algorithm:
     * Check if every adjacency list has length n-1
     */
    return false;
}

// ============================================================================
// Display and Utility
// ============================================================================

void displayList(AdjList *G) {
    /* TODO: Display adjacency list representation
     * Format:
     * Vertex 0: 1(5) -> 4(10) -> NULL
     * Vertex 1: 2(3) -> 3(2) -> NULL
     * Vertex 2: 3(1) -> NULL
     * Vertex 3: 0(4) -> NULL
     *
     * Where number in parentheses is edge weight
     * Use -> to show linked list structure
     */
}

void displayListAsMatrix(AdjList *G) {
    /* TODO: Display in matrix format (for comparison)
     * Build temporary matrix from adjacency lists
     * Then display in matrix format
     */
}

AdjList buildSampleListGraph(bool isDirected) {
    /* TODO: Build a sample graph for testing
     * Create graph with 5-6 vertices and various edges
     * Should match the sample matrix graph for comparison
     */
    AdjList G;
    return G;
}

void freeListGraph(AdjList *G) {
    /* TODO: Free all allocated memory
     * Algorithm:
     * 1. For each adjacency list:
     *    - Traverse list freeing each edge node
     * 2. Free the array of list heads
     * 3. Set numVertices to 0
     */
}
