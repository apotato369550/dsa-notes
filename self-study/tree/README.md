# Tree Data Structures - Training Ground

A comprehensive collection of tree implementations based on Aho's "Data Structures and Algorithms" book. This directory follows the same pattern as `adt_list_mania` for consistent, systematic practice.

## Directory Structure

```
tree/
├── tree.h                   # Common type definitions for ALL tree types
├── general_tree.h/.c        # General trees (Aho Section 3.2)
├── binary_tree.h/.c         # Basic binary trees
├── binary_search_tree.h/.c  # Binary search trees (Aho Section 5.1)
├── expression_tree.h/.c     # Expression trees (Aho Section 3.6)
├── huffman_tree.h/.c        # Huffman coding trees (Aho Section 3.4)
├── main.c                   # Test driver (to be implemented)
└── README.md                # This file
```

## File Organization Pattern

Following the `adt_list_mania` pattern:

1. **tree.h** - Shared type definitions (like `studtype.h`)
   - All tree node structures
   - Common typedefs
   - No function declarations

2. **{tree_type}.h** - Function declarations for each tree type
   - Operations from Aho's book
   - Additional utility functions
   - Clear documentation of algorithms

3. **{tree_type}.c** - Function implementations
   - Each function has `/* TODO */` placeholder
   - Detailed algorithm comments from Aho
   - Ready for you to implement

4. **main.c** - Testing framework (create this)
   - Similar to `adt_list_mania/main.c`
   - Menu-driven interface
   - Test each tree type independently

## Tree Types Covered

### 1. General Trees (`general_tree.h/.c`)
**Based on:** Aho Section 3.2

**Representation:** Leftmost-child, right-sibling

**Key Operations:**
- `parent(n)` - Get parent of node
- `leftmostChild(n)` - Get first child
- `rightSibling(n)` - Get next sibling
- `getLabel(n)` - Get node's label
- `preorder/postorder/levelOrder` - Traversals
- `descendantCount(n)` - Count descendants (Sec 3.6)
- `isDescendant(x, y)` - Test descendant relationship

**Practice Focus:** Understanding tree traversals, parent-child relationships

---

### 2. Binary Trees (`binary_tree.h/.c`)
**Based on:** Standard binary tree operations

**Key Operations:**
- `leftChild(n)` / `rightChild(n)` - Navigate children
- `preorder/inorder/postorder` - Three main traversals
- `isFullBinaryTree()` - Check if every node has 0 or 2 children
- `isCompleteBinaryTree()` - Check level-filling property
- `mirrorTree()` - Create reflection of tree
- `areIdentical()` - Compare two trees

**Practice Focus:** Binary tree properties, traversal differences

---

### 3. Binary Search Trees (`binary_search_tree.h/.c`)
**Based on:** Aho Section 5.1

**BST Property:** left < node < right (recursively)

**Core Operations from Aho:**
- `member(T, x)` - Search for element
- `insert(T, x)` - Add element
- `deleteElement(T, x)` - Remove element (3 cases!)
- `min(T)` / `max(T)` - Find extremes
- `deleteMin(T)` / `deleteMax(T)` - Remove extremes

**Additional Operations:**
- `successor(T, n)` / `predecessor(T, n)` - Inorder navigation
- `isValidBST()` - Verify BST property
- `kthSmallest(T, k)` - Find kth element
- `rangeQuery(T, min, max)` - Find elements in range
- `buildFromSortedArray()` - Create balanced BST

**Practice Focus:** Binary search, the 3 deletion cases, BST property

---

### 4. Expression Trees (`expression_tree.h/.c`)
**Based on:** Aho Section 3.6

**Structure:**
- Leaves = operands (numbers)
- Interior nodes = operators (+, -, *, /)

**Key Operations:**
- `buildFromPostfix(expr)` - Parse postfix notation
- `buildFromPrefix(expr)` - Parse prefix notation
- `buildFromInfix(expr)` - Parse infix notation
- `evaluate(T)` - Calculate result (postorder traversal!)
- `toPrefix(T)` - Convert to prefix (preorder)
- `toPostfix(T)` - Convert to postfix (postorder)
- `toInfix(T)` - Convert to infix (inorder)
- `simplifyConstants(T)` - Evaluate constant subexpressions

**Practice Focus:** Understanding how traversals relate to expression notations

---

### 5. Huffman Trees (`huffman_tree.h/.c`)
**Based on:** Aho Section 3.4

**Purpose:** Optimal prefix codes for data compression

**Key Operations:**
- `buildHuffmanTree(charFreqs, n)` - **Main algorithm**
  1. Create forest of single-node trees
  2. Repeatedly merge two lightest trees
  3. Until one tree remains
- `extractCodes(T)` - Get binary codes for each character
- `encode(text, codes)` - Compress text
- `decode(encoded, T)` - Decompress text
- `averageCodeLength()` - Measure compression
- Forest operations: `extractTwoLightest()`

**Practice Focus:** Greedy algorithms, weighted trees, priority queues

---

## Implementation Strategy

### Phase 1: Start Simple
1. Begin with **Binary Tree** (simplest structure)
2. Implement basic operations: create nodes, traversals
3. Test thoroughly before moving on

### Phase 2: Add Constraints
4. Move to **Binary Search Tree**
5. Focus on maintaining BST property
6. Master the 3 deletion cases

### Phase 3: Applications
7. **Expression Trees** - see traversals in action
8. **Huffman Trees** - complete algorithm

### Phase 4: General
9. **General Trees** - most flexible, uses different representation

## How to Practice

1. **Pick a tree type** (start with binary_tree)

2. **Implement one function at a time**
   - Read the `/* TODO */` comments
   - Check algorithm from Aho's book
   - Write the implementation
   - Test immediately in main.c

3. **Test thoroughly**
   - Create sample trees
   - Test edge cases (empty tree, single node, etc.)
   - Verify traversal orders

4. **Move to next function**

5. **Once complete, move to next tree type**

## Compilation

For each tree type, compile with:

```bash
# Example for binary search tree
gcc -o bst_test main.c binary_search_tree.c -I.

# Example for expression tree
gcc -o expr_test main.c expression_tree.c -I.

# Example for all trees (once main.c supports it)
gcc -o tree_test main.c general_tree.c binary_tree.c \
    binary_search_tree.c expression_tree.c huffman_tree.c -I.
```

## Key Algorithms to Master

### Tree Traversals
- **Preorder:** Node → Left → Right
- **Inorder:** Left → Node → Right (BST: sorted order!)
- **Postorder:** Left → Right → Node (for deletion, evaluation)
- **Level-order:** Breadth-first (needs queue)

### BST Deletion (3 Cases)
1. **Leaf:** Just remove it
2. **One child:** Replace with child
3. **Two children:** Replace with successor/predecessor

### Huffman Algorithm
1. Create forest of single-node trees
2. While forest has > 1 tree:
   - Extract two lightest
   - Merge them
   - Add back to forest
3. Remaining tree is Huffman tree

## Common Patterns

### Recursive Tree Operations
```c
int countNodes(Tree T) {
    if (T == NULL) return 0;
    return 1 + countNodes(T->left) + countNodes(T->right);
}
```

### Tree Traversal Template
```c
void preorder(Tree T) {
    if (T == NULL) return;
    visit(T);           // Process node
    preorder(T->left);  // Recurse left
    preorder(T->right); // Recurse right
}
```

### BST Search Template
```c
Node* search(BST T, int x) {
    if (T == NULL || T->data == x) return T;
    if (x < T->data) return search(T->left, x);
    return search(T->right, x);
}
```

## Notes

- All operations use `/* TODO */` placeholders
- Algorithm hints provided in comments
- Based directly on Aho's book sections
- Type definitions centralized in `tree.h`
- Ready for systematic implementation practice

## Next Steps

1. Implement `main.c` with menu system (like `adt_list_mania`)
2. Start implementing functions in chosen tree type
3. Test each function as you complete it
4. Move through tree types systematically

---

**Happy Tree Practicing!** 🌳
