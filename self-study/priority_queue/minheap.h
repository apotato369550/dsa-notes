#ifndef MINHEAP
#define MINHEAP

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include "heap.h"

// ============================================================================
// MIN HEAP OPERATIONS (Based on Aho Section 4.7)
// ============================================================================
// Min Heap Property: Parent <= Children (for all nodes)
//
// Example Min Heap:
//        2
//       / \
//      3   5
//     / \ / \
//    7  4 8  10
//
// Array: [2, 3, 5, 7, 4, 8, 10]
//
// Key invariant: elem[parent] <= elem[child] for ALL nodes

// Initialize empty min heap
void initialize(Minheap *M);

// Insert element into min heap (O(log n))
void insert(Minheap *M, int x);

// Remove and return minimum element (O(log n))
int deleteMin(Minheap *M);

// Empty the heap
void makeNull(Minheap *M);

// Restore heap property by moving element UP (used after insert)
void heapifyUp(Minheap *M, int i);

// Restore heap property by moving element DOWN (used after deleteMin)
void heapifyDown(Minheap *M, int i);

#endif
