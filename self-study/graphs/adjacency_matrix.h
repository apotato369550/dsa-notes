#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// ADJACENCY MATRIX GRAPH OPERATIONS (Based on Aho Section 6.2)
// ============================================================================
// Best for: Dense graphs, frequent edge existence checks
// Time: O(1) for edge lookup, O(n²) space
// Drawback: O(n²) space even for sparse graphs

// ----------------------------------------------------------------------------
// Basic Graph Operations
// ----------------------------------------------------------------------------

// Initialize graph with n vertices
void initMatrixGraph(AdjMatrix *G, int numVertices, bool isDirected);

// Add edge from u to v with given weight
// For undirected graphs, also adds v to u
void addEdgeMatrix(AdjMatrix *G, Vertex u, Vertex v, int weight);

// Remove edge from u to v
void removeEdgeMatrix(AdjMatrix *G, Vertex u, Vertex v);

// Check if edge exists from u to v
bool hasEdgeMatrix(AdjMatrix *G, Vertex u, Vertex v);

// Get weight of edge from u to v (returns INFINITY if no edge)
int getEdgeWeightMatrix(AdjMatrix *G, Vertex u, Vertex v);

// Get number of edges in graph
int countEdgesMatrix(AdjMatrix *G);

// ----------------------------------------------------------------------------
// ADT Operations from Aho Section 6.2
// ----------------------------------------------------------------------------

// FIRST(v) - Returns first vertex adjacent to v (NIL if none)
Vertex firstMatrix(AdjMatrix *G, Vertex v);

// NEXT(v, i) - Returns next vertex after i adjacent to v (NIL if i is last)
Vertex nextMatrix(AdjMatrix *G, Vertex v, Vertex i);

// VERTEX(v, i) - Returns vertex at index i (for matrix, just returns i)
Vertex vertexMatrix(Vertex v, Vertex i);

// ----------------------------------------------------------------------------
// Graph Properties
// ----------------------------------------------------------------------------

// Get degree of vertex (outgoing edges for directed graph)
int degreeMatrix(AdjMatrix *G, Vertex v);

// Get in-degree of vertex (for directed graphs)
int inDegreeMatrix(AdjMatrix *G, Vertex v);

// Check if graph is empty (no edges)
bool isEmptyMatrix(AdjMatrix *G);

// Check if graph is complete (all possible edges exist)
bool isCompleteMatrix(AdjMatrix *G);

// ----------------------------------------------------------------------------
// Display and Utility
// ----------------------------------------------------------------------------

// Display adjacency matrix
void displayMatrix(AdjMatrix *G);

// Display as adjacency list format (for comparison)
void displayMatrixAsList(AdjMatrix *G);

// Build sample graph for testing
AdjMatrix buildSampleMatrixGraph(bool isDirected);

// Free any allocated memory (minimal for matrix, but included for consistency)
void freeMatrixGraph(AdjMatrix *G);

#endif
