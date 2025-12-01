#include "heapsort.h"

void initialize(List *M)  {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

// ============================================================================
// HEAPSORT METHOD 1: Build Heap via Repeated Insertions
// ============================================================================
// INTUITION: Build a min heap by inserting each element one-by-one,
//            then extract all elements to get sorted order
//
// TIME: O(n log n) + O(n log n) = O(n log n)
//   - n insertions × O(log n) each = O(n log n)
//   - n deletions × O(log n) each = O(n log n)
//
// VISUAL EXAMPLE: Sort [5, 3, 8, 1, 9]
//
// Step 1: Build heap by inserting
//   Insert 5: [5]
//   Insert 3: [3, 5]        (3 bubbles up)
//   Insert 8: [3, 5, 8]
//   Insert 1: [1, 3, 8, 5]  (1 bubbles to root)
//   Insert 9: [1, 3, 8, 5, 9]
//
// Step 2: Extract all elements
//   Delete: 1 → Array becomes [1, _, _, _, _]
//   Delete: 3 → Array becomes [1, 3, _, _, _]
//   Delete: 5 → Array becomes [1, 3, 5, _, _]
//   Delete: 8 → Array becomes [1, 3, 5, 8, _]
//   Delete: 9 → Array becomes [1, 3, 5, 8, 9]
//
// Result: [1, 3, 5, 8, 9] - SORTED!

void heapSortV1(List *L) {
    List newList;
    newList.lastElem = -1;

    // PHASE 1: Build heap by inserting all elements
    // Each insert takes O(log i) where i is current heap size
    // Total: O(n log n)
    for (int i = 0; i <= L->lastElem; i++) {
        insert(&newList, L->elem[i]);
    }

    // PHASE 2: Extract all elements in sorted order
    // Each deleteMin takes O(log i) where i is current heap size
    // Total: O(n log n)
    for (int i = 0; i <= L->lastElem; i++) {
        int deleted = deleteMin(&newList);  // Get minimum
        newList.elem[i] = deleted;           // Place in sorted position
    }

    // Update lastElem to reflect sorted array size
    newList.lastElem = L->lastElem;

    // Copy sorted array back to original
    *L = newList;
}

// ============================================================================
// HEAPSORT METHOD 2: Build Heap via Bottom-Up Heapify (FASTER!)
// ============================================================================
// INTUITION: Instead of inserting one-by-one, start with unsorted array
//            and "fix" it from bottom-up to make it a heap
//
// WHY FASTER? Bottom-up heapify is O(n), not O(n log n)!
//   - Most elements are near leaves (low height)
//   - Only a few elements near root need to sink far
//   - Mathematical analysis proves this is O(n)
//
// TIME: O(n) + O(n log n) = O(n log n) with better constant
//
// STRATEGY: Start from LAST PARENT (not last leaf!)
//           Heapify each parent going backwards to root
//
// WHY START FROM LAST PARENT?
//   - Leaves are already trivial heaps (no children)
//   - Parents need their subtrees to be heaps first
//   - Going bottom-up ensures subtrees are heaps before we fix parent
//
// LAST PARENT FORMULA: floor(n/2) - 1
//   For n=11 nodes: floor(11/2)-1 = 4
//   Nodes 5-10 are leaves, node 4 is last parent
//
// VISUAL EXAMPLE: Heapify [9, 5, 3, 7, 1, 8, 2, 4, 6]
//
// Initial array (not a heap!):
//        9
//       / \
//      5   3
//     / \ / \
//    7  1 8  2
//   / \
//  4   6
//
// Last parent is at index floor(9/2)-1 = 3 (value 7)
//
// Step 1: Heapify from index 3 (value 7) down to leaves
//   Nothing happens (7 > 4 and 7 > 6, already a heap)
//
// Step 2: Heapify from index 2 (value 3)
//   3 > 2, swap → [9, 5, 2, 7, 1, 8, 3, 4, 6]
//
// Step 3: Heapify from index 1 (value 5)
//   5 > 1, swap → [9, 1, 2, 7, 5, 8, 3, 4, 6]
//
// Step 4: Heapify from index 0 (value 9)
//   9 > 1, swap → [1, 9, 2, 7, 5, 8, 3, 4, 6]
//   9 > 5, swap → [1, 5, 2, 7, 9, 8, 3, 4, 6]
//
// Now it's a MIN HEAP! Time: O(n)

void heapSortV2(List *L) {
    // YOUR COMMENT: "formula for leftmost interior node is floor(n/2)-1"
    // CORRECT! But you want to heapify from LAST PARENT, not leftmost interior

    // PHASE 1: Build heap via bottom-up heapify - O(n)
    //
    // Start from last parent (rightmost interior node)
    // Formula: floor((n-1)/2) where n = lastElem + 1
    // Or equivalently: floor(lastElem/2)
    //
    // For array of size 11 (indices 0-10):
    //   Last parent = floor(10/2) = 5
    //   Indices 6-10 are leaves

    int lastParent = floor(L->lastElem / 2);

    // Heapify each parent from last parent up to root
    // This builds the heap in O(n) time!
    for (int i = lastParent; i >= 0; i--) {
        heapifyDown(L, i);  // Fix heap property at position i
    }

    // PHASE 2: Extract all elements - O(n log n)
    int oldLastElem = L->lastElem;

    for (int i = 0; i <= oldLastElem; i++) {
        int deleted = deleteMin(L);      // Remove min (shrinks heap)
        L->elem[L->lastElem + 1] = deleted;  // Place at end (sorted region)
    }

    L->lastElem = oldLastElem;  // Restore size (now sorted)
}

void insert(List *M, int x)  {
    if (M->lastElem >= MAX - 1) return;
    M->elem[++M->lastElem] = x;
    heapifyUp(M, M->lastElem);
}

void makeNull(Heap *M)  {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void heapifyUp(List *M, int i) {
    if (i == 0) return;
    int child = i;
    int parent = floor((child - 1) / 2);
    while (i != 0 && M->elem[child] < M->elem[parent]) {
        int temp = M->elem[child];
        M->elem[child] = M->elem[parent];
        M->elem[parent] = temp;

        // bug: forgot to reassign values for child and parent
        // fix: reassign child with parent, and parent using the parent formula
        child = parent;
        parent = floor((child - 1) / 2);
    }
}

int deleteMin(Minheap *M) {
    // bug: no return type for int function
    // fix: return EMPTY instead
    if (M->lastElem < 0) return EMPTY;

    // bug: semantic error. variable named 'max' instead of 'min'
    int min = M->elem[0];
    M->elem[0] = M->elem[M->lastElem--];
    heapifyDown(M, 0);
    return min;
}

void heapifyDown(Minheap *M, int i) {
    // While i is not a leaf node (has at least one child)

    // bug: wrong boundary check. compared with MAX instead of M->lastElem
    // fix: changed MAX to M->lastElem;
    int leftChildIndex = (i * 2) + 1;
    bool hasLeftChild = leftChildIndex <= M->lastElem;

    int rightChildIndex = (i * 2) + 2;
    bool hasRightChild = rightChildIndex <= M->lastElem;

    int temp = 0;

    while (hasLeftChild || hasRightChild) {
        // CASE 1: Both children exist - find smaller child
        if (hasLeftChild && hasRightChild) {
            // bug: apparently, when both children exist, we need to find the smaller child
            // if the parent is bigger than the child, swap, otherwise, break.
            int smallerChildIndex = (M->elem[leftChildIndex] < M->elem[rightChildIndex])
                                    ? leftChildIndex : rightChildIndex;

            if (M->elem[i] > M->elem[smallerChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[smallerChildIndex];
                M->elem[smallerChildIndex] = temp;
                i = smallerChildIndex;
            } else {
                break;  // Heap property satisfied
            }

        // CASE 2: Only left child
        } else if (hasLeftChild) {
            if (M->elem[i] > M->elem[leftChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[leftChildIndex];
                M->elem[leftChildIndex] = temp;
                i = leftChildIndex;
            } else {
                // bug: forgot to break if POT is satisfied
                // fix: break statement
                break;
            }

        // CASE 3: Only right child
        } else if (hasRightChild) {
            if (M->elem[i] > M->elem[rightChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[rightChildIndex];
                M->elem[rightChildIndex] = temp;
                i = rightChildIndex;
            } else {
                // bug: forgot to break if POT is satisfied
                // fix: break statement
                break;
            }
        }

        // bug: forgot to update for next iteration
        // fix: update next iteration
        leftChildIndex = (i * 2) + 1;
        hasLeftChild = leftChildIndex <= M->lastElem;

        rightChildIndex = (i * 2) + 2;
        hasRightChild = rightChildIndex <= M->lastElem;
    }

    // YOUR COMMENT: "i think this logic is sound, but it's very redundant HAHAHAHAHA"
    // YES! You're absolutely right. The cleaner version from CODE_REVIEW_PQ.md
    // eliminates all this redundancy. But your logic is CORRECT!
}
