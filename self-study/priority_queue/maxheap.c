#include "maxheap.h"

void initialize(Maxheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Maxheap *M, int x) {
    // bug: off by one error
    // fix: M->lastElem >= MAX - 1
    if (M->lastElem >= MAX - 1) return;

    // STEP 1: Add new element at END of array (maintains complete tree property)
    M->elem[++M->lastElem] = x;

    // STEP 2: Restore heap property by bubbling up
    heapifyUp(M, M->lastElem);
}

int deleteMax(Maxheap *M) {
    // bug: no return value
    // fix: return EMPTY
    if (M->lastElem < 0) return EMPTY;

    // STEP 1: Save max (at root)
    int max = M->elem[0];

    // STEP 2: Move LAST element to root (maintains complete tree, breaks heap property)
    M->elem[0] = M->elem[M->lastElem--];

    // STEP 3: Restore heap property by bubbling down
    heapifyDown(M, 0);

    return max;
}

void makeNull(Maxheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

// ============================================================================
// HEAPIFY UP - THE INTUITION
// ============================================================================
// WHEN: After inserting at END of heap
// WHY: New element might be larger than its parent (violates max heap property)
// HOW: Bubble element UP by swapping with parent until parent >= element
//
// Visual Example - Insert 15 into max heap:
//
// Before insert:        After insert (heap property violated!):
//        10                     10
//       /  \                   /  \
//      8    5                 8    5
//     / \                    / \  /
//    3  7                   3  7 15  <- New element violates property!
//
// Step 1: Compare 15 with parent 5
//        10                     10
//       /  \                   /  \
//      8    5                 8    15  <- Swap! 15 > 5
//     / \  /                 / \  /
//    3  7 15                3  7 5
//
// Step 2: Compare 15 with parent 10
//        10                     15  <- Swap! 15 > 10
//       /  \                   /  \
//      8    15                8    10
//     / \  /                 / \  /
//    3  7 5                 3  7 5
//
// Step 3: 15 is now root, DONE! Heap property restored.

void heapifyUp(Maxheap *M, int i) {
    if (i == 0) return;  // Already at root, can't go up

    int child = i;
    int parent = floor((child - 1) / 2);

    // Keep swapping with parent while child > parent
    // INTUITION: "Bubble" large element UP until it finds its place
    while (i != 0 && M->elem[child] > M->elem[parent]) {
        // Swap child with parent
        int temp = M->elem[child];
        M->elem[child] = M->elem[parent];
        M->elem[parent] = temp;

        // bug: no variable update (causes infinite loop!)
        // fix: update child and parent for next iteration
        child = parent;                    // Move up to parent's position
        parent = floor((child - 1) / 2);   // Calculate new parent
    }

    // LOOP INVARIANT: After each iteration, heap property is satisfied
    // for the path from original position to current child position
}

// ============================================================================
// HEAPIFY DOWN - THE INTUITION
// ============================================================================
// WHEN: After moving last element to root (deleteMax)
// WHY: Root element might be smaller than its children (violates max heap property)
// HOW: Sink element DOWN by swapping with LARGER child until both children <= element
//
// KEY INSIGHT: Always swap with LARGER child! (not just any child)
// If you swap with smaller child, the larger child becomes parent of smaller one,
// which would violate the heap property.
//
// Visual Example - Delete max (10) from heap:
//
// Before delete:        After moving last to root (property violated!):
//        10                     4   <- Last element at root, too small!
//       /  \                   / \
//      8    5                 8   5
//     / \  /                 / \
//    3  7 4                 3  7
//
// Step 1: Compare 4 with children 8 and 5
//         - Larger child is 8
//         - 4 < 8, so swap with 8
//        4                      8   <- Swap with LARGER child
//       / \                    / \
//      8   5                  4   5
//     / \                    / \
//    3  7                   3  7
//
// Step 2: Compare 4 with children 3 and 7
//         - Larger child is 7
//         - 4 < 7, so swap with 7
//        8                      8
//       / \                    / \
//      4   5                  7   5  <- Swap with LARGER child
//     / \                    / \
//    3  7                   3  4
//
// Step 3: 4 is now a leaf, DONE! Heap property restored.

void heapifyDown(Maxheap *M, int i) {
    // STRATEGY: Find larger child, compare with parent, swap if needed, repeat

    // While i is not a leaf node (has at least one child)
    int leftChildIndex = (i * 2) + 1;
    bool hasLeftChild = leftChildIndex <= M->lastElem;

    int rightChildIndex = (i * 2) + 2;
    bool hasRightChild = rightChildIndex <= M->lastElem;

    int temp = 0;

    while (hasLeftChild || hasRightChild) {

        // CASE 1: Both children exist
        // INTUITION: Must swap with LARGER child to maintain heap property
        if (hasLeftChild && hasRightChild) {
            // Find which child is larger
            int largerChildIndex = (M->elem[leftChildIndex] > M->elem[rightChildIndex])
                                   ? leftChildIndex : rightChildIndex;

            // Compare parent with larger child
            if (M->elem[i] < M->elem[largerChildIndex]) {
                // Parent too small, swap with larger child
                temp = M->elem[i];
                M->elem[i] = M->elem[largerChildIndex];
                M->elem[largerChildIndex] = temp;
                i = largerChildIndex;  // Move down
            } else {
                // Parent >= both children, heap property satisfied!
                break;
            }

        // CASE 2: Only left child exists
        } else if (hasLeftChild) {
            if (M->elem[i] < M->elem[leftChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[leftChildIndex];
                M->elem[leftChildIndex] = temp;
                i = leftChildIndex;
            } else {
                // bug: missing break statement
                // fix: add break statement
                break;
            }

        // CASE 3: Only right child exists (shouldn't happen in complete tree!)
        } else if (hasRightChild) {
            if (M->elem[i] < M->elem[rightChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[rightChildIndex];
                M->elem[rightChildIndex] = temp;
                i = rightChildIndex;
            } else {
                // bug: missing break statement
                // fix: add break statement
                break;
            }
        }

        // Update for next iteration
        leftChildIndex = (i * 2) + 1;
        hasLeftChild = leftChildIndex <= M->lastElem;

        rightChildIndex = (i * 2) + 2;
        hasRightChild = rightChildIndex <= M->lastElem;
    }

    // LOOP INVARIANT: After each iteration, heap property is satisfied
    // for subtrees rooted at i's children

    // YOUR COMMENT: "i think this logic is sound, but it's very redundant"
    // YOU'RE RIGHT! See the cleaner version in your CODE_REVIEW_PQ.md
    // The refactored version uses one loop that finds the largest of
    // (parent, left, right) and swaps if needed. Much cleaner!
}
