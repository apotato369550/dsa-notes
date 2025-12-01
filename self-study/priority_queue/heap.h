#ifndef MY_HEAP
#define MY_HEAP

#include <limits.h>

#define MAX 21
#define EMPTY INT_MIN

// ============================================================================
// HEAP STRUCTURE (Based on Aho Section 4.7)
// ============================================================================
// Array-based binary heap representation
// Complete binary tree stored in array where:
//   - Parent of node i is at floor((i-1)/2)
//   - Left child of node i is at 2*i + 1
//   - Right child of node i is at 2*i + 2
//
// WHY ARRAY? Complete binary trees pack perfectly into arrays with NO GAPS!
//
// Visual example:
//        1              Array: [1, 3, 2, 7, 4, 5, 6]
//       / \             Index:  0  1  2  3  4  5  6
//      3   2
//     / \ / \           Parent formula: floor((i-1)/2)
//    7  4 5  6          Left child: 2*i + 1
//                       Right child: 2*i + 2

typedef struct {
    int elem[MAX];      // Array storing heap elements
    int lastElem;       // Index of last element (size - 1)
                        // Empty heap has lastElem = -1
                        // Full heap has lastElem = MAX - 1
} Heap, Minheap, Maxheap, List;

#endif
