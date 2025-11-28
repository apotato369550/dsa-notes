#include "adjacency_matrix.h"

// ============================================================================
// Basic Graph Operations
// ============================================================================

void initMatrixGraph(AdjMatrix *G, int numVertices, bool isDirected) {
    /* TODO: Initialize adjacency matrix graph
     * Algorithm:
     * 1. Set G->numVertices = numVertices
     * 2. Set G->isDirected = isDirected
     * 3. Initialize all matrix entries to INFINITY (no edges)
     * 4. Set diagonal to 0 (distance from vertex to itself)
     */
}

void addEdgeMatrix(AdjMatrix *G, Vertex u, Vertex v, int weight) {
    /* TODO: Add edge from u to v with given weight
     * Algorithm:
     * 1. Set G->adjMatrix[u][v] = weight
     * 2. If undirected graph, also set G->adjMatrix[v][u] = weight
     */
}

void removeEdgeMatrix(AdjMatrix *G, Vertex u, Vertex v) {
    /* TODO: Remove edge from u to v
     * Algorithm:
     * 1. Set G->adjMatrix[u][v] = INFINITY
     * 2. If undirected, also set G->adjMatrix[v][u] = INFINITY
     */
}

bool hasEdgeMatrix(AdjMatrix *G, Vertex u, Vertex v) {
    /* TODO: Check if edge exists from u to v
     * Return true if G->adjMatrix[u][v] != INFINITY
     */
    return false;
}

int getEdgeWeightMatrix(AdjMatrix *G, Vertex u, Vertex v) {
    /* TODO: Return weight of edge from u to v
     * Return G->adjMatrix[u][v] (will be INFINITY if no edge)
     */
    return INFINITY;
}

int countEdgesMatrix(AdjMatrix *G) {
    /* TODO: Count number of edges in graph
     * Algorithm:
     * For directed graph:
     *   Count all non-INFINITY entries (except diagonal)
     * For undirected graph:
     *   Count non-INFINITY entries above diagonal, multiply by 2
     *   OR count all and divide by 2
     */
    return 0;
}

// ============================================================================
// ADT Operations from Aho Section 6.2
// ============================================================================

Vertex firstMatrix(AdjMatrix *G, Vertex v) {
    /* TODO: Return first vertex adjacent to v
     * Algorithm:
     * Scan row v from column 0 to n-1
     * Return first column j where adjMatrix[v][j] != INFINITY
     * Return NIL if no adjacent vertices
     */
    return NIL;
}

Vertex nextMatrix(AdjMatrix *G, Vertex v, Vertex i) {
    /* TODO: Return next vertex after i adjacent to v
     * Algorithm:
     * Scan row v from column i+1 to n-1
     * Return first column j where adjMatrix[v][j] != INFINITY
     * Return NIL if no more adjacent vertices
     */
    return NIL;
}

Vertex vertexMatrix(Vertex v, Vertex i) {
    /* TODO: For matrix representation, index IS the vertex
     * Simply return i
     */
    return i;
}

// ============================================================================
// Graph Properties
// ============================================================================

int degreeMatrix(AdjMatrix *G, Vertex v) {
    /* TODO: Get degree (number of outgoing edges) of vertex v
     * Algorithm:
     * Count number of non-INFINITY entries in row v (except diagonal)
     */
    return 0;
}

int inDegreeMatrix(AdjMatrix *G, Vertex v) {
    /* TODO: Get in-degree (number of incoming edges) of vertex v
     * Algorithm:
     * Count number of non-INFINITY entries in column v (except diagonal)
     */
    return 0;
}

bool isEmptyMatrix(AdjMatrix *G) {
    /* TODO: Check if graph has no edges
     * Return true if all off-diagonal entries are INFINITY
     */
    return true;
}

bool isCompleteMatrix(AdjMatrix *G) {
    /* TODO: Check if graph is complete (all possible edges exist)
     * For directed: all n(n-1) possible edges exist
     * For undirected: all n(n-1)/2 possible edges exist
     * Algorithm:
     * Check if all off-diagonal entries are != INFINITY
     */
    return false;
}

// ============================================================================
// Display and Utility
// ============================================================================

void displayMatrix(AdjMatrix *G) {
    /* TODO: Display adjacency matrix
     * Format:
     *       0   1   2   3
     *   0   0   5  INF INF
     *   1  INF  0   3   2
     *   2  INF INF  0   1
     *   3   4  INF INF  0
     *
     * Use "INF" or "∞" for INFINITY values
     */
}

void displayMatrixAsList(AdjMatrix *G) {
    /* TODO: Display in adjacency list format (for comparison)
     * Format:
     * 0: 1(5)
     * 1: 2(3) 3(2)
     * 2: 3(1)
     * 3: 0(4)
     *
     * Where number in parentheses is edge weight
     */
}

AdjMatrix buildSampleMatrixGraph(bool isDirected) {
    /* TODO: Build a sample graph for testing
     * Create a graph with 5-6 vertices and various edges
     * Example: Small road network or simple social network
     */
    AdjMatrix G;
    return G;
}

void freeMatrixGraph(AdjMatrix *G) {
    /* TODO: Free any allocated memory
     * For basic matrix implementation, matrix is statically allocated
     * Just set numVertices to 0 for safety
     * (More relevant if using dynamic allocation)
     */
}
