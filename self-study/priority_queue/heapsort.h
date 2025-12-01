#ifndef HEAPSORT
#define HEAPSORT

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"

// ============================================================================
// HEAPSORT (Based on Aho Section 7.6)
// ============================================================================
// Heapsort uses a heap to sort in O(n log n) time
//
// TWO METHODS to build the initial heap:
//
// METHOD 1 (heapSortV1): INSERT one by one
//   - Insert n elements: n × O(log n) = O(n log n)
//   - Extract n elements: n × O(log n) = O(n log n)
//   - TOTAL: O(n log n)
//
// METHOD 2 (heapSortV2): HEAPIFY bottom-up
//   - Heapify from last parent up to root: O(n) [BETTER!]
//   - Extract n elements: n × O(log n) = O(n log n)
//   - TOTAL: O(n log n) but with better constant factor
//
// KEY INSIGHT: Method 2 is faster because heapify is O(n), not O(n log n)

void initialize(List *L);

// METHOD 1: Build heap by inserting each element (O(n log n))
void heapSortV1(List *L);

// METHOD 2: Build heap by heapifying bottom-up (O(n) + O(n log n) = O(n log n))
void heapSortV2(List *L);

void insert(List *L, int x);
void makeNull(List *L);
void heapifyUp(List *L, int i);

// Delete minimum and return it
int deleteMin(List *L);

// Restore heap property downward
void heapifyDown(List *M, int i);

#endif
