#include "minheap.h"

void initialize(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

void insert(Minheap *M, int x) {
    // bug: off by one error on M->lastElem >= MAX
    // fix: M->lastElem >= MAX - 1
    if (M->lastElem >= MAX - 1) return;

    // STEP 1: Add at END (maintains complete tree)
    M->elem[++M->lastElem] = x;

    // STEP 2: Bubble up to restore min heap property
    heapifyUp(M, M->lastElem);
}

int deleteMin(Minheap *M) {
    // bug: no return type for int function
    // fix: return EMPTY instead
    if (M->lastElem < 0) return EMPTY;

    // bug: semantic error. variable named 'max' instead of 'min'
    // STEP 1: Save minimum (at root)
    int min = M->elem[0];

    // STEP 2: Move last element to root
    M->elem[0] = M->elem[M->lastElem--];

    // STEP 3: Sink down to restore min heap property
    heapifyDown(M, 0);

    return min;
}

void makeNull(Minheap *M) {
    for (int i = 0; i < MAX; M->elem[i] = EMPTY, i++) {}
    M->lastElem = -1;
}

// ============================================================================
// HEAPIFY UP FOR MIN HEAP
// ============================================================================
// SAME LOGIC as max heap, but comparison is REVERSED
// Bubble UP while child < parent (instead of child > parent)

void heapifyUp(Minheap *M, int i) {
    if (i == 0) return;
    int child = i;
    int parent = floor((child - 1) / 2);

    // Keep swapping while child SMALLER than parent
    // (For max heap, it was: while child LARGER than parent)
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

// ============================================================================
// HEAPIFY DOWN FOR MIN HEAP
// ============================================================================
// SAME LOGIC as max heap, but swap with SMALLER child (not larger)
//
// KEY INSIGHT: Always swap with SMALLER child!
// Example: Parent is 10, left child is 3, right child is 5
//   - Must swap with 3 (smaller child)
//   - If we swap with 5, then 3 would be child of 5, violating min heap!
//
// YOUR CODE BELOW is correct logic but redundant (as you noted!)
// The cleaner version is in CODE_REVIEW_PQ.md lines 369-397

void heapifyDown(Minheap *M, int i) {
    // While i is not a leaf node (has at least one child)

    // bug: wrong boundary check. compared with MAX instead of M->lastElem
    // fix: changed MAX to M->lastElem
    int leftChildIndex = (i * 2) + 1;
    bool hasLeftChild = leftChildIndex <= M->lastElem;

    int rightChildIndex = (i * 2) + 2;
    bool hasRightChild = rightChildIndex <= M->lastElem;

    int temp = 0;

    while (hasLeftChild || hasRightChild) {
        // CASE 1: Both children exist
        if (hasLeftChild && hasRightChild) {
            // bug: apparently, when both children exist, we need to find the smaller child
            // CORRECT! Must swap with SMALLER child for min heap
            int smallerChildIndex = (M->elem[leftChildIndex] < M->elem[rightChildIndex])
                                    ? leftChildIndex : rightChildIndex;

            if (M->elem[i] > M->elem[smallerChildIndex]) {
                temp = M->elem[i];
                M->elem[i] = M->elem[smallerChildIndex];
                M->elem[smallerChildIndex] = temp;
                i = smallerChildIndex;
            } else {
                break;  // Heap property satisfied!
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

        // CASE 3: Only right child (shouldn't happen in complete tree!)
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
    // YES! The cleaner way (from CODE_REVIEW_PQ.md):
    //
    // while (1) {
    //     int smallest = i;  // Assume parent is smallest
    //     if (leftChild exists && leftChild < smallest)
    //         smallest = leftChild;
    //     if (rightChild exists && rightChild < smallest)
    //         smallest = rightChild;
    //     if (smallest == i) break;  // Parent is smallest, done!
    //     swap(i, smallest);
    //     i = smallest;
    // }
    //
    // Much cleaner! One unified logic instead of three cases.
}
