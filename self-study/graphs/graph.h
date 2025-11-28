#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <limits.h>

// Maximum number of vertices in graph
#define MAX_VERTICES 100

// Sentinel values
#define INFINITY INT_MAX
#define NIL -1

// ============================================================================
// VERTEX AND EDGE TYPES
// ============================================================================

typedef int Vertex;  // Vertices numbered 0 to n-1

// Edge/Arc for adjacency list representation
typedef struct EdgeNode {
    Vertex dest;              // Destination vertex
    int weight;               // Edge weight/cost (1 for unweighted)
    struct EdgeNode *next;    // Next edge in list
} EdgeNode, *Edge;

// ============================================================================
// ADJACENCY MATRIX REPRESENTATION (Section 6.2)
// ============================================================================
// Best for dense graphs or when need O(1) edge lookup

typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];  // Cost matrix (INFINITY if no edge)
    int numVertices;                             // Number of vertices
    bool isDirected;                             // true for digraph, false for undirected
} AdjMatrix, MatrixGraph;

// ============================================================================
// ADJACENCY LIST REPRESENTATION (Section 6.2)
// ============================================================================
// Best for sparse graphs, space proportional to |V| + |E|

typedef struct {
    Edge *adjList;          // Array of adjacency lists (size numVertices)
    int numVertices;        // Number of vertices
    bool isDirected;        // true for digraph, false for undirected
} AdjList, ListGraph;

// ============================================================================
// GRAPH TRAVERSAL DATA STRUCTURES
// ============================================================================

// Mark status for vertices during traversal
typedef enum {
    UNVISITED,
    VISITED,
    FINISHED
} MarkStatus;

// Edge types discovered during DFS (Section 6.5)
typedef enum {
    TREE_EDGE,      // Edge to unvisited vertex
    BACK_EDGE,      // Edge to ancestor
    FORWARD_EDGE,   // Edge to proper descendant (directed graphs only)
    CROSS_EDGE      // Edge between non-ancestor/descendant (directed graphs only)
} EdgeType;

// Traversal result data
typedef struct {
    int parent[MAX_VERTICES];       // Parent in DFS/BFS tree (-1 if root)
    int distance[MAX_VERTICES];     // Distance from source (BFS) or finish time (DFS)
    int discoveryTime[MAX_VERTICES]; // Discovery time (DFS only)
    int finishTime[MAX_VERTICES];   // Finish time (DFS only)
    MarkStatus mark[MAX_VERTICES];  // Visited status
} TraversalData;

// ============================================================================
// SHORTEST PATH DATA STRUCTURES (Dijkstra, Floyd)
// ============================================================================

// Single-source shortest path result (Dijkstra - Section 6.3)
typedef struct {
    int dist[MAX_VERTICES];     // Distance from source
    int pred[MAX_VERTICES];     // Predecessor on shortest path
    bool inSet[MAX_VERTICES];   // true if shortest path known
} ShortestPathData;

// All-pairs shortest path result (Floyd - Section 6.4)
typedef struct {
    int dist[MAX_VERTICES][MAX_VERTICES];  // Distance between all pairs
    int path[MAX_VERTICES][MAX_VERTICES];  // Intermediate vertex for path reconstruction
} AllPairsData;

// ============================================================================
// MINIMUM SPANNING TREE DATA STRUCTURES (Section 7.2)
// ============================================================================

// Edge for MST algorithms
typedef struct {
    Vertex u, v;    // Endpoints
    int weight;     // Edge weight
} MSTEdge;

// MST result
typedef struct {
    MSTEdge edges[MAX_VERTICES - 1];  // MST has exactly n-1 edges
    int numEdges;                      // Should equal numVertices - 1
    int totalCost;                     // Sum of edge weights
} MSTResult;

// For Kruskal's algorithm - MERGE-FIND set operations
typedef struct {
    int parent[MAX_VERTICES];   // Parent in union-find tree
    int rank[MAX_VERTICES];     // Rank for union by rank
} UnionFind;

#endif
