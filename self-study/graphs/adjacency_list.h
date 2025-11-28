#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// ADJACENCY LIST GRAPH OPERATIONS (Based on Aho Section 6.2)
// ============================================================================
// Best for: Sparse graphs, iterating through neighbors
// Space: O(|V| + |E|) - proportional to vertices + edges
// Time: O(degree(v)) to iterate neighbors, O(degree(v)) to check specific edge

// ----------------------------------------------------------------------------
// Basic Graph Operations
// ----------------------------------------------------------------------------

// Initialize graph with n vertices
void initListGraph(AdjList *G, int numVertices, bool isDirected);

// Add edge from u to v with given weight
// For undirected graphs, also adds v to u
void addEdgeList(AdjList *G, Vertex u, Vertex v, int weight);

// Remove edge from u to v
void removeEdgeList(AdjList *G, Vertex u, Vertex v);

// Check if edge exists from u to v
bool hasEdgeList(AdjList *G, Vertex u, Vertex v);

// Get weight of edge from u to v (returns INFINITY if no edge)
int getEdgeWeightList(AdjList *G, Vertex u, Vertex v);

// Get number of edges in graph
int countEdgesList(AdjList *G);

// ----------------------------------------------------------------------------
// ADT Operations from Aho Section 6.2
// ----------------------------------------------------------------------------

// FIRST(v) - Returns first vertex adjacent to v (NIL if none)
Edge firstList(AdjList *G, Vertex v);

// NEXT(v, e) - Returns edge after e in adjacency list of v
Edge nextList(AdjList *G, Vertex v, Edge e);

// VERTEX(v, e) - Returns destination vertex of edge e
Vertex vertexList(Vertex v, Edge e);

// ----------------------------------------------------------------------------
// Edge Node Operations (Helper Functions)
// ----------------------------------------------------------------------------

// Create a new edge node
EdgeNode* createEdgeNode(Vertex dest, int weight);

// Insert edge at front of adjacency list
void insertEdgeFront(Edge *list, Vertex dest, int weight);

// Remove edge to dest from adjacency list
void removeEdgeFromList(Edge *list, Vertex dest);

// Find edge to dest in adjacency list (returns pointer or NULL)
EdgeNode* findEdgeInList(Edge list, Vertex dest);

// ----------------------------------------------------------------------------
// Graph Properties
// ----------------------------------------------------------------------------

// Get degree of vertex (number of outgoing edges)
int degreeList(AdjList *G, Vertex v);

// Get in-degree of vertex (for directed graphs - requires traversing all lists)
int inDegreeList(AdjList *G, Vertex v);

// Check if graph is empty (no edges)
bool isEmptyList(AdjList *G);

// Check if graph is complete (all possible edges exist)
bool isCompleteList(AdjList *G);

// ----------------------------------------------------------------------------
// Display and Utility
// ----------------------------------------------------------------------------

// Display adjacency list representation
void displayList(AdjList *G);

// Display as adjacency matrix format (for comparison)
void displayListAsMatrix(AdjList *G);

// Build sample graph for testing
AdjList buildSampleListGraph(bool isDirected);

// Free all allocated memory
void freeListGraph(AdjList *G);

#endif
