#ifndef MAXHEAP
#define MAXHEAP

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include "heap.h"

// ============================================================================
// MAX HEAP OPERATIONS (Based on Aho Section 4.7)
// ============================================================================
// Max Heap Property: Parent >= Children (for all nodes)
//
// Example Max Heap:
//        10
//       /  \
//      8    5
//     / \  / \
//    3  7 2  4
//
// Array: [10, 8, 5, 3, 7, 2, 4]
//
// Key invariant: elem[parent] >= elem[child] for ALL nodes

// Initialize empty max heap
void initialize(Maxheap *M);

// Insert element into max heap (O(log n))
void insert(Maxheap *M, int x);

// Remove and return maximum element (O(log n))
int deleteMax(Maxheap *M);

// Empty the heap
void makeNull(Maxheap *M);

// Restore heap property by moving element UP (used after insert)
void heapifyUp(Maxheap *M, int i);

// Restore heap property by moving element DOWN (used after deleteMax)
void heapifyDown(Maxheap *M, int i);

#endif
