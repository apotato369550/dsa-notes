#ifndef HEAPSORT
#define HEAPSORT

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"

// i wonder if we can replace heapify up/down with regular heapfiy
void initialize(List *L);

// method 1 of heapsort: insert till full to make pot, then spam deleteMin
// time complexity: O(n log n)
void heapSortV1(List *L);

// method 2 of heapsort: heapify till POT, and then spam deleteMin
// time complexity: O((n/2) log n)
void heapSortV2(List *L);

void insert(List *L, int x);
void makeNull(List *L);

void heapifyUp(List *L, int i);

// deleteMin utility to delete all elements from pot to convert to list
int deleteMin(List *L);

// heapify helper function for deleteMin
void heapifyDown(List *M, int i);

#endif