# Priority Queue (Heap) - Training Ground

A comprehensive collection of heap implementations based on Aho's "Data Structures and Algorithms" Section 4.7. Preserves your original code with enhanced intuition-building comments.

## Directory Structure

```
priority_queue/
├── heap.h                  # Common type definitions for all heaps
├── maxheap.h/.c            # Max heap implementation
├── minheap.h/.c            # Min heap implementation
├── heapsort.h/.c           # Two heapsort methods
├── CODE_REVIEW_PQ.md       # Your comprehensive bug analysis
└── README.md               # This file
```

## Core Concepts

### What is a Heap?

A **heap** is a **complete binary tree** that satisfies the **heap property**:

- **Max Heap**: Parent ≥ Children (root is maximum)
- **Min Heap**: Parent ≤ Children (root is minimum)

### Why Array Representation?

Complete binary trees pack **perfectly** into arrays with **NO GAPS**!

```
Tree:           1              Array: [1, 3, 2, 7, 4, 5, 6]
               / \             Index:  0  1  2  3  4  5  6
              3   2
             / \ / \
            7  4 5  6
```

**Navigation formulas** (0-indexed):
- **Parent of i**: `floor((i-1)/2)`
- **Left child of i**: `2*i + 1`
- **Right child of i**: `2*i + 2`

**Why this works**: Complete trees fill level-by-level, left-to-right

---

## The Two Key Operations

### 1. HeapifyUp (Bubble Up)

**WHEN**: After inserting at END of heap

**WHY**: New element might violate heap property with parent

**HOW**: Swap with parent repeatedly until heap property restored

**TIME**: O(log n) - at most height of tree

**INTUITION**: Think of a bubble rising to surface
- Large values "float up" in max heap
- Small values "float up" in min heap

**Visual Example** (Max Heap - Insert 15):
```
Before:        10              After insert:       10
              /  \                                /  \
             8    5                              8    5
            / \                                 / \  /
           3  7                                3  7 15  ← VIOLATES!

Step 1: Compare with parent 5
           10                                  10
          /  \                                /  \
         8    15  ← Swap!                    8    15
        / \  /                              / \  /
       3  7 5                              3  7 5

Step 2: Compare with parent 10
           15  ← Swap!                     15  ← DONE!
          /  \                            /  \
         8    10                         8    10
        / \  /                          / \  /
       3  7 5                          3  7 5
```

**Key Code Pattern**:
```c
while (child has parent && child violates heap property) {
    swap(child, parent);
    child = parent;           // Move up
    parent = parent's parent;
}
```

---

### 2. HeapifyDown (Sink Down)

**WHEN**: After moving last element to root (delete operation)

**WHY**: Root element might violate heap property with children

**HOW**: Swap with appropriate child repeatedly until heap property restored

**TIME**: O(log n) - at most height of tree

**CRITICAL INSIGHT**: Must swap with **extreme child** (larger for max heap, smaller for min heap)

**WHY?** If you swap with wrong child, siblings will violate heap property!

**Example**: Parent=10, Left=3, Right=5 (MIN HEAP)
- ❌ **WRONG**: Swap 10 with 5 → 3 becomes child of 5 (violates min heap!)
- ✅ **CORRECT**: Swap 10 with 3 → 5 remains larger than 3 (maintains min heap)

**Visual Example** (Max Heap - Delete max):
```
Before:        10              After moving last to root:
              /  \                        4  ← Too small!
             8    5                      / \
            / \  /                      8   5
           3  7 4                      / \
                                      3  7

Step 1: Compare with children 8 and 5
        Larger child is 8
        4 < 8, so swap with 8
           8  ← Swap with LARGER           8
          / \                             / \
         4   5                           4   5
        / \                             / \
       3  7                            3  7

Step 2: Compare with children 3 and 7
        Larger child is 7
        4 < 7, so swap with 7
           8                              8
          / \                            / \
         7   5  ← Swap with LARGER      7   5
        / \                            / \
       3  4                           3  4  ← DONE!
```

**Key Code Pattern**:
```c
while (parent has at least one child) {
    find extreme child (max for max heap, min for min heap);
    if (parent violates property with extreme child) {
        swap(parent, extreme child);
        parent = extreme child;  // Move down
    } else {
        break;  // Heap property satisfied!
    }
}
```

---

## Heapsort - Two Methods

Both sort in **O(n log n)** but with different approaches:

### Method 1: Build Heap via Insertions

**Strategy**: Insert elements one-by-one, then extract all

**Time Complexity**:
- Build heap: n insertions × O(log n) = **O(n log n)**
- Extract all: n deletions × O(log n) = **O(n log n)**
- **Total: O(n log n)**

**Visual**: Sort [5, 3, 8, 1, 9]
```
Insert phase:
  [5] → [3,5] → [3,5,8] → [1,3,8,5] → [1,3,8,5,9]

Extract phase:
  Delete 1: [1,_,_,_,_]
  Delete 3: [1,3,_,_,_]
  Delete 5: [1,3,5,_,_]
  Delete 8: [1,3,5,8,_]
  Delete 9: [1,3,5,8,9]

Result: [1,3,5,8,9] ✓ SORTED
```

---

### Method 2: Build Heap via Bottom-Up Heapify (FASTER!)

**Strategy**: Start with unsorted array, heapify from bottom-up

**Time Complexity**:
- Build heap: Bottom-up heapify = **O(n)** ← FASTER!
- Extract all: n deletions × O(log n) = **O(n log n)**
- **Total: O(n log n)** with better constant factor

**WHY IS HEAPIFY O(n)?**
- Most nodes are near leaves (small height)
- Only few nodes near root sink far
- Mathematical analysis: Σ(nodes at height h × h) = O(n)

**KEY FORMULA**: Last parent = `floor(lastElem / 2)`

**WHY START FROM LAST PARENT?**
- Leaves are already trivial heaps (no children to fix)
- Parents need subtrees to be heaps first
- Bottom-up ensures subtrees are heaps before fixing parent

**Visual**: Heapify [9, 5, 3, 7, 1, 8, 2, 4, 6]
```
Initial (NOT a heap):
        9
       / \
      5   3
     / \ / \
    7  1 8  2
   / \
  4   6

Last parent = floor(8/2) = 4 (value 1)

Step 1: Heapify from index 4 (value 1) - already ok
Step 2: Heapify from index 3 (value 7) - already ok
Step 3: Heapify from index 2 (value 3)
  3 > 2, swap → [9,5,2,7,1,8,3,4,6]

Step 4: Heapify from index 1 (value 5)
  5 > 1, swap → [9,1,2,7,5,8,3,4,6]

Step 5: Heapify from index 0 (value 9)
  9 > 1, swap → [1,9,2,7,5,8,3,4,6]
  9 > 5, swap → [1,5,2,7,9,8,3,4,6]

Result: VALID MIN HEAP in O(n) time!
```

---

## Common Mistakes & Intuitions

### Mistake 1: Forgetting to Update Loop Variables

**Your original bug**:
```c
while (i != 0 && M->elem[child] > M->elem[parent]) {
    swap(child, parent);
    // BUG: Infinite loop! child and parent never updated
}
```

**Why it matters**: Without update, you swap same elements forever

**Fix**:
```c
child = parent;
parent = floor((child - 1) / 2);
```

---

### Mistake 2: Comparing with MAX Instead of lastElem

**Your original bug**:
```c
bool hasLeftChild = leftChildIndex < MAX;  // WRONG!
```

**Why it matters**: Checks array size, not heap size. May access uninitialized memory!

**Fix**:
```c
bool hasLeftChild = leftChildIndex <= M->lastElem;  // Heap size
```

---

### Mistake 3: Swapping with Wrong Child

**The critical error in heapifyDown**:

For **MIN HEAP**: Must swap with **SMALLER** child
```c
// Find smaller child first!
int smallerChild = (left < right) ? left : right;
if (parent > smallerChild) {
    swap(parent, smallerChild);
}
```

For **MAX HEAP**: Must swap with **LARGER** child
```c
// Find larger child first!
int largerChild = (left > right) ? left : right;
if (parent < largerChild) {
    swap(parent, largerChild);
}
```

**Why?** Ensures siblings maintain heap property with each other!

---

### Mistake 4: Not Breaking When Heap Property Satisfied

**Your original bug**:
```c
if (M->elem[i] >= M->elem[child]) {
    // BUG: Forgot to break!
    // Loop continues unnecessarily
}
```

**Why it matters**: Wastes time, may cause incorrect swaps

**Fix**: Always break when heap property satisfied!

---

## Your Code Refactoring Note

**You noted**: "i think this logic is sound, but it's very redundant HAHAHAHAHA"

**You're absolutely right!** Your CODE_REVIEW_PQ.md has the cleaner version:

### Your Current Approach (Correct but Verbose):
```c
if (hasLeft && hasRight) {
    // Find extreme child, swap if needed
} else if (hasLeft) {
    // Check left only
} else if (hasRight) {
    // Check right only
}
```

### Cleaner Approach (From Your Review):
```c
while (1) {
    int extreme = i;  // Assume parent is extreme

    if (hasLeft && elem[left] is more extreme)
        extreme = left;
    if (hasRight && elem[right] is more extreme)
        extreme = right;

    if (extreme == i) break;  // Heap property satisfied!

    swap(i, extreme);
    i = extreme;
}
```

**Why cleaner?**
- Unified logic for all cases
- No redundant swap code
- Single termination condition
- Easier to read and maintain

---

## Time Complexity Summary

| Operation | Time | Why |
|-----------|------|-----|
| **Insert** | O(log n) | Bubble up at most height of tree |
| **DeleteMin/Max** | O(log n) | Sink down at most height of tree |
| **Heapify (bottom-up)** | O(n) | Most nodes at low height |
| **Heapsort Method 1** | O(n log n) | n inserts + n deletes |
| **Heapsort Method 2** | O(n log n) | O(n) heapify + n deletes |
| **FindMin/Max** | O(1) | Always at root |

---

## Practice Exercises

1. **Trace heapifyUp**: Insert 20 into max heap [15, 10, 8, 5, 3]

2. **Trace heapifyDown**: Delete max from [15, 10, 8, 5, 3, 1]

3. **Build heap**: Use bottom-up heapify on [7, 3, 9, 1, 5]

4. **Why swap with extreme?**: Prove swapping with non-extreme child breaks heap property

5. **Compare methods**: When is Method 2 better than Method 1?

---

## Key Takeaways

✅ **Heaps use arrays** - complete trees pack perfectly

✅ **HeapifyUp** - bubble violating element UP to restore property

✅ **HeapifyDown** - sink violating element DOWN, **always swap with extreme child**

✅ **Heapsort Method 2 faster** - O(n) heapify beats O(n log n) insertions

✅ **Your code is correct** - just a bit verbose. Refactored version is cleaner!

---

**Keep practicing those heapify operations - the intuition will click!** 🎯
