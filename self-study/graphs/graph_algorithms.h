#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "graph.h"
#include "adjacency_matrix.h"
#include "adjacency_list.h"
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// GRAPH TRAVERSAL ALGORITHMS
// ============================================================================

// ----------------------------------------------------------------------------
// Depth-First Search (Section 6.5 - Directed, Section 7.3 - Undirected)
// ----------------------------------------------------------------------------

// DFS on adjacency list from source vertex
void dfsListFromVertex(AdjList *G, Vertex source, TraversalData *result);

// DFS on adjacency matrix from source vertex
void dfsMatrixFromVertex(AdjMatrix *G, Vertex source, TraversalData *result);

// DFS all vertices (handles disconnected graphs)
void dfsListAll(AdjList *G, TraversalData *result);

// DFS all vertices on matrix graph
void dfsMatrixAll(AdjMatrix *G, TraversalData *result);

// Classify edge type during DFS (tree, back, forward, cross)
EdgeType classifyEdge(Vertex u, Vertex v, TraversalData *data);

// ----------------------------------------------------------------------------
// Breadth-First Search (Section 7.3)
// ----------------------------------------------------------------------------

// BFS on adjacency list from source vertex
void bfsListFromVertex(AdjList *G, Vertex source, TraversalData *result);

// BFS on adjacency matrix from source vertex
void bfsMatrixFromVertex(AdjMatrix *G, Vertex source, TraversalData *result);

// BFS all vertices (handles disconnected graphs)
void bfsListAll(AdjList *G, TraversalData *result);

// BFS all vertices on matrix graph
void bfsMatrixAll(AdjMatrix *G, TraversalData *result);

// ============================================================================
// SHORTEST PATH ALGORITHMS
// ============================================================================

// ----------------------------------------------------------------------------
// Dijkstra's Algorithm (Section 6.3) - Single-Source Shortest Paths
// ----------------------------------------------------------------------------

// Dijkstra on adjacency matrix (O(n²))
void dijkstraMatrix(AdjMatrix *G, Vertex source, ShortestPathData *result);

// Dijkstra on adjacency list with simple array scan (O(n²))
void dijkstraList(AdjList *G, Vertex source, ShortestPathData *result);

// Print shortest path from source to dest
void printShortestPath(ShortestPathData *data, Vertex source, Vertex dest);

// Check if path exists from source to dest
bool hasPath(ShortestPathData *data, Vertex dest);

// ----------------------------------------------------------------------------
// Floyd-Warshall Algorithm (Section 6.4) - All-Pairs Shortest Paths
// ----------------------------------------------------------------------------

// Floyd's algorithm on adjacency matrix (O(n³))
void floydWarshall(AdjMatrix *G, AllPairsData *result);

// Print shortest path from u to v using path reconstruction
void printFloydPath(AllPairsData *data, Vertex u, Vertex v);

// ----------------------------------------------------------------------------
// Warshall's Algorithm (Section 6.4) - Transitive Closure
// ----------------------------------------------------------------------------

// Compute transitive closure (path existence matrix)
void warshall(AdjMatrix *G, bool closure[MAX_VERTICES][MAX_VERTICES]);

// ============================================================================
// MINIMUM SPANNING TREE ALGORITHMS (Undirected Graphs Only)
// ============================================================================

// ----------------------------------------------------------------------------
// Prim's Algorithm (Section 7.2)
// ----------------------------------------------------------------------------

// Prim's MST on adjacency matrix (O(n²))
void primMatrix(AdjMatrix *G, MSTResult *result);

// Prim's MST on adjacency list
void primList(AdjList *G, MSTResult *result);

// ----------------------------------------------------------------------------
// Kruskal's Algorithm (Section 7.2)
// ----------------------------------------------------------------------------

// Kruskal's MST using union-find (O(e log e))
void kruskal(AdjMatrix *G, MSTResult *result);

// Kruskal's MST on adjacency list
void kruskalList(AdjList *G, MSTResult *result);

// Display MST result
void displayMST(MSTResult *mst);

// ============================================================================
// UNION-FIND DATA STRUCTURE (For Kruskal's Algorithm)
// ============================================================================

// Initialize union-find structure
void initUnionFind(UnionFind *uf, int numVertices);

// Find root of element (with path compression)
int find(UnionFind *uf, int x);

// Union two sets by rank
void unionSets(UnionFind *uf, int x, int y);

// Check if two elements in same set
bool sameSet(UnionFind *uf, int x, int y);

// ============================================================================
// ADVANCED GRAPH ALGORITHMS
// ============================================================================

// ----------------------------------------------------------------------------
// Topological Sort (Section 6.6) - DAGs Only
// ----------------------------------------------------------------------------

// Topological sort using DFS (returns ordering in array)
bool topologicalSort(AdjList *G, Vertex *ordering, int *orderSize);

// Check if graph is a DAG (Directed Acyclic Graph)
bool isDAG(AdjList *G);

// ----------------------------------------------------------------------------
// Strongly Connected Components (Section 6.7) - Directed Graphs
// ----------------------------------------------------------------------------

// Find all strongly connected components
int findSCC(AdjList *G, int components[MAX_VERTICES]);

// Check if graph is strongly connected
bool isStronglyConnected(AdjList *G);

// ----------------------------------------------------------------------------
// Connected Components (Section 7.3) - Undirected Graphs
// ----------------------------------------------------------------------------

// Find all connected components
int findConnectedComponents(AdjList *G, int components[MAX_VERTICES]);

// Check if graph is connected
bool isConnected(AdjList *G);

// ----------------------------------------------------------------------------
// Biconnected Components and Articulation Points (Section 7.4)
// ----------------------------------------------------------------------------

// Find all articulation points
int findArticulationPoints(AdjList *G, Vertex artPoints[MAX_VERTICES]);

// Check if graph is biconnected
bool isBiconnected(AdjList *G);

// ============================================================================
// CYCLE DETECTION
// ============================================================================

// Detect cycle in directed graph
bool hasCycleDirected(AdjList *G);

// Detect cycle in undirected graph
bool hasCycleUndirected(AdjList *G);

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

// Initialize traversal data
void initTraversalData(TraversalData *data, int numVertices);

// Print DFS/BFS tree
void printTraversalTree(TraversalData *data, int numVertices);

#endif
