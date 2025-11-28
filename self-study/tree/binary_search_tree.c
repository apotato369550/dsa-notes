#include "binary_search_tree.h"

// ============================================================================
// Basic ADT Operations from Aho
// ============================================================================

void initBST(BST *T) {
    /* TODO: Initialize BST to NULL */
}

void makeNullBST(BST *T) {
    /* TODO: Free all nodes and set T to NULL
     * Use freeBST helper function
     */
}

bool member(BST T, int x) {
    /* TODO: Test if element x is in BST
     * Algorithm (from Aho Section 5.1):
     * 1. If tree is NULL, return false
     * 2. If x == current node's data, return true
     * 3. If x < current node's data, search left subtree
     * 4. If x > current node's data, search right subtree
     */
    return false;
}

void insert(BST *T, int x) {
    /* TODO: Insert element x into BST
     * Algorithm (from Aho Section 5.1):
     * 1. If tree is empty, create new node as root
     * 2. Otherwise, compare x with current node:
     *    - If x < current, go left
     *    - If x > current, go right
     *    - If x == current, do nothing (element already exists)
     * 3. When reaching NULL position, insert new node there
     */
}

void deleteElement(BST *T, int x) {
    /* TODO: Delete element x from BST
     * Algorithm (from Aho Section 5.1) - Three cases:
     *
     * Case 1: Node is a leaf
     *   - Simply remove it
     *
     * Case 2: Node has one child
     *   - Replace node with its child
     *
     * Case 3: Node has two children
     *   - Replace with minimum element from right subtree, OR
     *   - Replace with maximum element from left subtree
     *   - Then delete that replacement node (which falls into case 1 or 2)
     */
}

int min(BST T) {
    /* TODO: Find minimum element in BST
     * Algorithm (from Aho Section 5.1):
     * Follow left child pointers until reaching node with no left child
     * That node contains the minimum
     */
    return -1; // Return appropriate error value
}

int max(BST T) {
    /* TODO: Find maximum element in BST
     * Algorithm (mirror of min):
     * Follow right child pointers until reaching node with no right child
     * That node contains the maximum
     */
    return -1; // Return appropriate error value
}

int deleteMin(BST *T) {
    /* TODO: Remove and return smallest element
     * Algorithm (from Aho Section 5.1):
     * 1. Find leftmost node (has no left child)
     * 2. Save its value
     * 3. Replace it with its right child (may be NULL)
     * 4. Return saved value
     */
    return -1; // Return appropriate error value
}

int deleteMax(BST *T) {
    /* TODO: Remove and return largest element
     * Algorithm (mirror of deleteMin):
     * 1. Find rightmost node (has no right child)
     * 2. Save its value
     * 3. Replace it with its left child (may be NULL)
     * 4. Return saved value
     */
    return -1; // Return appropriate error value
}

// ============================================================================
// BST Navigation Operations
// ============================================================================

BSTNode* findBSTNode(BST T, int x) {
    /* TODO: Find and return pointer to node containing x
     * Similar to member(), but returns node pointer instead of bool
     */
    return NULL;
}

BSTNode* findMinNode(BST T) {
    /* TODO: Find and return pointer to node with minimum value
     * Follow left children until reaching node with no left child
     */
    return NULL;
}

BSTNode* findMaxNode(BST T) {
    /* TODO: Find and return pointer to node with maximum value
     * Follow right children until reaching node with no right child
     */
    return NULL;
}

BSTNode* successor(BST T, BSTNode *n) {
    /* TODO: Find inorder successor of node n
     * Inorder successor = next node in sorted order
     *
     * Algorithm:
     * Case 1: If n has right child
     *   - Successor is minimum node in right subtree
     * Case 2: If n has no right child
     *   - Go up using parent pointers until finding a node that is left child
     *   - That node's parent is the successor
     */
    return NULL;
}

BSTNode* predecessor(BST T, BSTNode *n) {
    /* TODO: Find inorder predecessor of node n
     * Inorder predecessor = previous node in sorted order
     *
     * Algorithm (mirror of successor):
     * Case 1: If n has left child
     *   - Predecessor is maximum node in left subtree
     * Case 2: If n has no left child
     *   - Go up using parent pointers until finding a node that is right child
     *   - That node's parent is the predecessor
     */
    return NULL;
}

// ============================================================================
// Tree Traversal Operations
// ============================================================================

void inorderBST(BST T) {
    /* TODO: Inorder traversal (Left -> Node -> Right)
     * Important: For BST, inorder traversal visits nodes in sorted order!
     */
}

void preorderBST(BST T) {
    /* TODO: Preorder traversal (Node -> Left -> Right) */
}

void postorderBST(BST T) {
    /* TODO: Postorder traversal (Left -> Right -> Node) */
}

void displayBST(BST T) {
    /* TODO: Display BST structure in readable format
     * Show tree sideways or with indentation
     */
}

// ============================================================================
// Tree Properties and Utilities
// ============================================================================

bool isBSTEmpty(BST T) {
    /* TODO: Check if BST is empty */
    return true;
}

int countBSTNodes(BST T) {
    /* TODO: Count total nodes in BST
     * Use recursion: 1 + count(left) + count(right)
     */
    return 0;
}

int bstHeight(BST T) {
    /* TODO: Calculate height of BST
     * Use recursion: 1 + max(height(left), height(right))
     */
    return -1;
}

bool isValidBST(BST T, int minValue, int maxValue) {
    /* TODO: Check if tree satisfies BST property
     * Useful for testing your implementation!
     *
     * Algorithm:
     * 1. If tree is NULL, return true
     * 2. If current node's value violates [minValue, maxValue] range, return false
     * 3. Recursively check:
     *    - Left subtree with range [minValue, current-1]
     *    - Right subtree with range [current+1, maxValue]
     */
    return false;
}

int countInRange(BST T, int minVal, int maxVal) {
    /* TODO: Count nodes with values in range [minVal, maxVal]
     * Use BST property to prune search:
     * - If current > maxVal, only search left
     * - If current < minVal, only search right
     * - Otherwise, search both
     */
    return 0;
}

// ============================================================================
// Advanced BST Operations
// ============================================================================

BST buildFromSortedArray(int *arr, int size) {
    /* TODO: Build balanced BST from sorted array
     * Algorithm:
     * 1. Middle element becomes root
     * 2. Recursively build left subtree from left half
     * 3. Recursively build right subtree from right half
     * This creates a balanced BST with height O(log n)
     */
    return NULL;
}

int kthSmallest(BST T, int k) {
    /* TODO: Find kth smallest element (k is 1-indexed)
     * Algorithm:
     * 1. Count nodes in left subtree
     * 2. If count+1 == k, current node is answer
     * 3. If k <= count, search left subtree
     * 4. If k > count+1, search right subtree for (k-count-1)th element
     */
    return -1;
}

int kthLargest(BST T, int k) {
    /* TODO: Find kth largest element (k is 1-indexed)
     * Algorithm: Similar to kthSmallest but traverse right first
     * OR: Find (n-k+1)th smallest where n = total nodes
     */
    return -1;
}

void rangeQuery(BST T, int minVal, int maxVal) {
    /* TODO: Print all elements in range [minVal, maxVal] in sorted order
     * Use inorder traversal with pruning:
     * - Only traverse left if current > minVal
     * - Only traverse right if current < maxVal
     * - Print current if minVal <= current <= maxVal
     */
}

int sumBST(BST T) {
    /* TODO: Calculate sum of all elements in BST
     * Use any traversal: sum(left) + current + sum(right)
     */
    return 0;
}

void freeBST(BST *T) {
    /* TODO: Free all nodes in BST using postorder traversal
     * Must free children before parent
     * Set T to NULL after freeing
     */
}
