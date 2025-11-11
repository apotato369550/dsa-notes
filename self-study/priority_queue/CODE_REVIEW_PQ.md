# Priority Queue Code Review

## Critical Bugs Found

### MINHEAP.C

#### Bug 1: Missing Return Value
**Error Type:** Syntax Error (Missing return value)
**Severity:** CRITICAL - Will not compile
**Function:** `deleteMin()`
**Line:** 16

**Issue:**
```c
if (M->lastElem < 0 ) return;
```
Function is declared to return `int` but `return` statement has no value.

**Fix:**
```c
if (M->lastElem < 0 ) return EMPTY;  // or return -1, or 0, depending on your error handling
```

---

#### Bug 2: Wrong Function Name in Header
**Error Type:** Semantic Error (Name mismatch)
**Severity:** CRITICAL - Will cause linker errors
**Function:** Header declaration
**Line:** minheap.h:18

**Issue:**
Header declares `int deleteMax(Minheap *M);` but implementation has `int deleteMin(Minheap *M);`

**Fix:**
In minheap.h line 18, change:
```c
int deleteMax(Minheap *M);
```
to:
```c
int deleteMin(Minheap *M);
```

---

#### Bug 3: Infinite Loop in heapifyUp
**Error Type:** Logic Error (Infinite loop)
**Severity:** CRITICAL - Will hang program
**Function:** `heapifyUp()`
**Lines:** 30-36

**Issue:**
Variables `child` and `parent` are never updated inside the while loop, causing infinite loop if condition is true.

**Fix:**
```c
void heapifyUp(Minheap *M, int i) {
    if (i == 0) return;
    int child = i;
    int parent = floor((child - 1) / 2);
    while (child != 0 && M->elem[child] < M->elem[parent]) {
        int temp = M->elem[child];
        M->elem[child] = M->elem[parent];
        M->elem[parent] = temp;
        // UPDATE VARIABLES
        child = parent;
        parent = floor((child - 1) / 2);
    }
}
```

---

#### Bug 4: Wrong Variable Name in deleteMin
**Error Type:** Semantic Error (Wrong variable name)
**Severity:** MEDIUM - Logic error, misleading variable name
**Function:** `deleteMin()`
**Line:** 17

**Issue:**
```c
int max = M->elem[0];
```
Variable is named `max` but should be `min` since this is a minheap.

**Fix:**
```c
int min = M->elem[0];
```
And update line 20:
```c
return min;
```

---

#### Bug 5: Off-by-one Error in insert
**Error Type:** Logic Error (Boundary check)
**Severity:** MEDIUM - Allows writing past array bounds
**Function:** `insert()`
**Line:** 9

**Issue:**
```c
if (M->lastElem >= MAX) return;
```
Should be `>= MAX - 1` because array indices go from 0 to MAX-1. If lastElem is already MAX-1, then `++M->lastElem` on line 10 will make it MAX, which is out of bounds.

**Fix:**
```c
if (M->lastElem >= MAX - 1) return;
```

---

#### Bug 6: Incorrect heapifyDown Logic (Both Children Case)
**Error Type:** Logic Error (Wrong comparison order)
**Severity:** HIGH - Violates heap property
**Function:** `heapifyDown()`
**Lines:** 56-72

**Issue:**
When both children exist, you need to find the SMALLER child first, then compare parent with that smaller child. Currently, you check left first, then right independently, which can swap with the wrong child.

**Fix:**
```c
if (hasLeftChild && hasRightChild) {
    // Find the smaller child
    int smallerChildIndex = (M->elem[leftChildIndex] < M->elem[rightChildIndex])
                            ? leftChildIndex : rightChildIndex;

    // Compare parent with smaller child
    if (M->elem[i] > M->elem[smallerChildIndex]) {
        temp = M->elem[i];
        M->elem[i] = M->elem[smallerChildIndex];
        M->elem[smallerChildIndex] = temp;
        i = smallerChildIndex;
    } else {
        break;  // Heap property satisfied, stop
    }
}
```

---

#### Bug 7: Missing Loop Termination in heapifyDown
**Error Type:** Logic Error (Missing break conditions)
**Severity:** HIGH - Can cause incorrect swaps or infinite loops
**Function:** `heapifyDown()`
**Lines:** 73-91

**Issue:**
After swapping in the `hasLeftChild` and `hasRightChild` only cases, if heap property is satisfied, the loop should break. Also, the boolean updates at the end of each case should be outside to update for the next iteration.

**Fix:**
```c
} else if (hasLeftChild) {
    if (M->elem[i] > M->elem[leftChildIndex]) {
        temp = M->elem[i];
        M->elem[i] = M->elem[leftChildIndex];
        M->elem[leftChildIndex] = temp;
        i = leftChildIndex;
    } else {
        break;  // Heap property satisfied
    }
} else if (hasRightChild) {
    if (M->elem[i] > M->elem[rightChildIndex]) {
        temp = M->elem[i];
        M->elem[i] = M->elem[rightChildIndex];
        M->elem[rightChildIndex] = temp;
        i = rightChildIndex;
    } else {
        break;  // Heap property satisfied
    }
} else {
    break;  // No children, done
}

// Update for next iteration
leftChildIndex = (i * 2) + 1;
hasLeftChild = leftChildIndex <= M->lastElem;

rightChildIndex = (i * 2) + 2;
hasRightChild = rightChildIndex <= M->lastElem;
```

---

#### Bug 8: Wrong Boundary Check in heapifyDown
**Error Type:** Logic Error (Wrong boundary condition)
**Severity:** HIGH - Can access uninitialized memory
**Function:** `heapifyDown()`
**Lines:** 45, 48, 64, 71, 80, 89

**Issue:**
Checking `leftChildIndex < MAX` and `rightChildIndex < MAX` is checking array bounds, but you should check against `M->lastElem` instead since `lastElem` tracks the actual heap size.

**Fix:**
Change all instances:
```c
hasLeftChild = leftChildIndex <= M->lastElem;
hasRightChild = rightChildIndex <= M->lastElem;
```

---

### MAXHEAP.C

#### Bug 9: Missing Return Value
**Error Type:** Syntax Error (Missing return value)
**Severity:** CRITICAL - Will not compile
**Function:** `deleteMax()`
**Line:** 15

**Issue:**
```c
if (M->lastElem < 0 ) return;
```
Function is declared to return `int` but `return` statement has no value.

**Fix:**
```c
if (M->lastElem < 0 ) return EMPTY;  // or return -1, or 0, depending on your error handling
```

---

#### Bug 10: Infinite Loop in heapifyUp
**Error Type:** Logic Error (Infinite loop)
**Severity:** CRITICAL - Will hang program
**Function:** `heapifyUp()`
**Lines:** 30-36

**Issue:**
Same as minheap - variables `child` and `parent` are never updated inside the while loop.

**Fix:**
```c
void heapifyUp(Maxheap *M, int i) {
    if (i == 0) return;
    int child = i;
    int parent = floor((child - 1) / 2);
    while (child != 0 && M->elem[child] > M->elem[parent]) {
        int temp = M->elem[child];
        M->elem[child] = M->elem[parent];
        M->elem[parent] = temp;
        // UPDATE VARIABLES
        child = parent;
        parent = floor((child - 1) / 2);
    }
}
```

---

#### Bug 11: Off-by-one Error in insert
**Error Type:** Logic Error (Boundary check)
**Severity:** MEDIUM - Allows writing past array bounds
**Function:** `insert()`
**Line:** 9

**Issue:**
Same as minheap.

**Fix:**
```c
if (M->lastElem >= MAX - 1) return;
```

---

#### Bug 12: Incorrect heapifyDown Logic (Both Children Case)
**Error Type:** Logic Error (Wrong comparison order)
**Severity:** HIGH - Violates heap property
**Function:** `heapifyDown()`
**Lines:** 56-70

**Issue:**
When both children exist, you need to find the LARGER child first, then compare parent with that larger child.

**Fix:**
```c
if (hasLeftChild && hasRightChild) {
    // Find the larger child
    int largerChildIndex = (M->elem[leftChildIndex] > M->elem[rightChildIndex])
                           ? leftChildIndex : rightChildIndex;

    // Compare parent with larger child
    if (M->elem[i] < M->elem[largerChildIndex]) {
        temp = M->elem[i];
        M->elem[i] = M->elem[largerChildIndex];
        M->elem[largerChildIndex] = temp;
        i = largerChildIndex;
    } else {
        break;  // Heap property satisfied, stop
    }
}
```

---

#### Bug 13: Missing Loop Termination in heapifyDown
**Error Type:** Logic Error (Missing break conditions)
**Severity:** HIGH - Can cause incorrect swaps or infinite loops
**Function:** `heapifyDown()`
**Lines:** 71-89

**Issue:**
Same as minheap - missing break conditions after heap property is satisfied.

**Fix:**
```c
} else if (hasLeftChild) {
    if (M->elem[i] < M->elem[leftChildIndex]) {
        temp = M->elem[i];
        M->elem[i] = M->elem[leftChildIndex];
        M->elem[leftChildIndex] = temp;
        i = leftChildIndex;
    } else {
        break;  // Heap property satisfied
    }
} else if (hasRightChild) {
    if (M->elem[i] < M->elem[rightChildIndex]) {
        temp = M->elem[i];
        M->elem[i] = M->elem[rightChildIndex];
        M->elem[rightChildIndex] = temp;
        i = rightChildIndex;
    } else {
        break;  // Heap property satisfied
    }
} else {
    break;  // No children, done
}

// Update for next iteration
leftChildIndex = (i * 2) + 1;
hasLeftChild = leftChildIndex <= M->lastElem;

rightChildIndex = (i * 2) + 2;
hasRightChild = rightChildIndex <= M->lastElem;
```

---

#### Bug 14: Wrong Boundary Check in heapifyDown
**Error Type:** Logic Error (Wrong boundary condition)
**Severity:** HIGH - Can access uninitialized memory
**Function:** `heapifyDown()`
**Lines:** 43, 46, 62, 69, 78, 87

**Issue:**
Same as minheap - should check against `M->lastElem` not `MAX`.

**Fix:**
Change all instances:
```c
hasLeftChild = leftChildIndex <= M->lastElem;
hasRightChild = rightChildIndex <= M->lastElem;
```

---

## BONUS: Refactored heapifyDown Function

Here's a cleaner, less redundant version of `heapifyDown()` for both heaps:

### For MINHEAP:
```c
void heapifyDown(Minheap *M, int i) {
    while (1) {
        int leftChildIndex = (i * 2) + 1;
        int rightChildIndex = (i * 2) + 2;
        int smallest = i;

        // Find smallest among parent, left child, and right child
        if (leftChildIndex <= M->lastElem && M->elem[leftChildIndex] < M->elem[smallest]) {
            smallest = leftChildIndex;
        }
        if (rightChildIndex <= M->lastElem && M->elem[rightChildIndex] < M->elem[smallest]) {
            smallest = rightChildIndex;
        }

        // If parent is already the smallest, heap property is satisfied
        if (smallest == i) {
            break;
        }

        // Swap parent with smallest child
        int temp = M->elem[i];
        M->elem[i] = M->elem[smallest];
        M->elem[smallest] = temp;

        // Move down to the child's position
        i = smallest;
    }
}
```

### For MAXHEAP:
```c
void heapifyDown(Maxheap *M, int i) {
    while (1) {
        int leftChildIndex = (i * 2) + 1;
        int rightChildIndex = (i * 2) + 2;
        int largest = i;

        // Find largest among parent, left child, and right child
        if (leftChildIndex <= M->lastElem && M->elem[leftChildIndex] > M->elem[largest]) {
            largest = leftChildIndex;
        }
        if (rightChildIndex <= M->lastElem && M->elem[rightChildIndex] > M->elem[largest]) {
            largest = rightChildIndex;
        }

        // If parent is already the largest, heap property is satisfied
        if (largest == i) {
            break;
        }

        // Swap parent with largest child
        int temp = M->elem[i];
        M->elem[i] = M->elem[largest];
        M->elem[largest] = temp;

        // Move down to the child's position
        i = largest;
    }
}
```

**Why This is Better:**
1. Eliminates redundant boolean variables and duplicate swap code
2. Uses a single comparison logic: find extreme (min/max) among parent and children
3. Clear termination condition: if parent is already extreme, stop
4. Recalculates indices each iteration (cleaner than tracking multiple state variables)
5. Much easier to read and maintain

---

## Summary

**Total Bugs Found:** 14

**By Severity:**
- CRITICAL: 5 (will not compile or will hang)
- HIGH: 6 (violates heap property or memory safety)
- MEDIUM: 3 (boundary issues, naming)

**Files Affected:**
- minheap.c: 8 bugs
- minheap.h: 1 bug
- maxheap.c: 5 bugs

Good luck with the fixes!
