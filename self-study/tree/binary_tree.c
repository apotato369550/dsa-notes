#include "binary_tree.h"

// ============================================================================
// Basic Operations
// ============================================================================

void initBinaryTree(BinaryTree *T) {
    /* TODO: Initialize tree to NULL */
}

BinaryTreeNode* createBinaryNode(int data, char label) {
    /* TODO: Allocate and initialize a new binary tree node
     * Set data, label, left=NULL, right=NULL, parent=NULL
     */
    return NULL;
}

void createBinaryRoot(BinaryTree *T, int data, char label) {
    /* TODO: Create root node for tree T */
}

BinaryTreeNode* leftChild(BinaryTreeNode *n) {
    /* TODO: Return left child of node n (NULL if none) */
    return NULL;
}

BinaryTreeNode* rightChild(BinaryTreeNode *n) {
    /* TODO: Return right child of node n (NULL if none) */
    return NULL;
}

BinaryTreeNode* binaryParent(BinaryTreeNode *n) {
    /* TODO: Return parent of node n (NULL if root or n is NULL) */
    return NULL;
}

bool isNull(BinaryTreeNode *n) {
    /* TODO: Check if node n is NULL */
    return true;
}

// ============================================================================
// Tree Construction Operations
// ============================================================================

void setLeftChild(BinaryTreeNode *parent, BinaryTreeNode *newChild) {
    /* TODO: Set left child of parent to newChild
     * Also set parent pointer of newChild
     */
}

void setRightChild(BinaryTreeNode *parent, BinaryTreeNode *newChild) {
    /* TODO: Set right child of parent to newChild
     * Also set parent pointer of newChild
     */
}

BinaryTree buildSampleBinaryTree() {
    /* TODO: Build a sample binary tree for testing
     * Example structure:
     *         1
     *       /   \
     *      2     3
     *     / \   /
     *    4   5 6
     */
    return NULL;
}

// ============================================================================
// Tree Traversal Operations
// ============================================================================

void preorderBinary(BinaryTree T) {
    /* TODO: Implement preorder traversal (Node -> Left -> Right)
     * Algorithm:
     * 1. Visit/print current node
     * 2. Recursively traverse left subtree
     * 3. Recursively traverse right subtree
     */
}

void inorderBinary(BinaryTree T) {
    /* TODO: Implement inorder traversal (Left -> Node -> Right)
     * Algorithm:
     * 1. Recursively traverse left subtree
     * 2. Visit/print current node
     * 3. Recursively traverse right subtree
     */
}

void postorderBinary(BinaryTree T) {
    /* TODO: Implement postorder traversal (Left -> Right -> Node)
     * Algorithm:
     * 1. Recursively traverse left subtree
     * 2. Recursively traverse right subtree
     * 3. Visit/print current node
     */
}

void levelOrderBinary(BinaryTree T) {
    /* TODO: Implement level-order (breadth-first) traversal
     * Algorithm:
     * 1. Use a queue to store nodes
     * 2. Enqueue root
     * 3. While queue not empty:
     *    - Dequeue node, visit it
     *    - Enqueue left child (if exists)
     *    - Enqueue right child (if exists)
     */
}

void displayBinaryTree(BinaryTree T) {
    /* TODO: Display tree in visual format
     * Example output:
     *       1
     *      / \
     *     2   3
     *    / \
     *   4   5
     */
}

// ============================================================================
// Tree Properties and Utilities
// ============================================================================

int countBinaryNodes(BinaryTree T) {
    /* TODO: Count total nodes in binary tree
     * Algorithm:
     * If tree is NULL, return 0
     * Otherwise, return 1 + count(left) + count(right)
     */
    return 0;
}

int binaryHeight(BinaryTree T) {
    /* TODO: Calculate height of binary tree
     * Height = number of edges on longest path from root to leaf
     * Empty tree has height -1, single node has height 0
     * Algorithm:
     * If tree is NULL, return -1
     * Otherwise, return 1 + max(height(left), height(right))
     */
    return -1;
}

bool isBinaryEmpty(BinaryTree T) {
    /* TODO: Check if binary tree is empty */
    return true;
}

bool isBinaryLeaf(BinaryTreeNode *n) {
    /* TODO: Check if node is a leaf (no children)
     * Node is leaf if both left and right are NULL
     */
    return false;
}

int countLeaves(BinaryTree T) {
    /* TODO: Count leaf nodes in tree
     * Algorithm:
     * If tree is NULL, return 0
     * If tree is leaf, return 1
     * Otherwise, return countLeaves(left) + countLeaves(right)
     */
    return 0;
}

bool isFullBinaryTree(BinaryTree T) {
    /* TODO: Check if tree is full binary tree
     * Full binary tree: every node has either 0 or 2 children
     * Algorithm:
     * If tree is NULL, return true
     * If tree is leaf, return true
     * If tree has only one child, return false
     * Otherwise, check both subtrees recursively
     */
    return false;
}

bool isCompleteBinaryTree(BinaryTree T) {
    /* TODO: Check if tree is complete binary tree
     * Complete binary tree: all levels are filled except possibly the last,
     * and the last level is filled from left to right
     * Algorithm: Use level-order traversal with a flag
     * - Once you encounter a node with missing child, all subsequent nodes must be leaves
     */
    return false;
}

// ============================================================================
// Advanced Operations
// ============================================================================

BinaryTreeNode* findNode(BinaryTree T, int data) {
    /* TODO: Find a node with given data (returns first occurrence)
     * Use any traversal (preorder recommended)
     * Return pointer to node if found, NULL otherwise
     */
    return NULL;
}

int getNodeLevel(BinaryTree T, BinaryTreeNode *target) {
    /* TODO: Get level of a node (root is at level 0)
     * Algorithm:
     * 1. Use level-order traversal with level tracking
     * 2. When target is found, return its level
     * 3. Return -1 if not found
     */
    return -1;
}

bool areIdentical(BinaryTree T1, BinaryTree T2) {
    /* TODO: Check if two trees are structurally identical
     * Two trees are identical if:
     * 1. Both are NULL, OR
     * 2. Both have same data, and
     * 3. Left subtrees are identical, and
     * 4. Right subtrees are identical
     */
    return false;
}

BinaryTree mirrorTree(BinaryTree T) {
    /* TODO: Create a mirror/reflection of the tree
     * Algorithm:
     * 1. If tree is NULL, return NULL
     * 2. Create new node with same data
     * 3. Left child of new node = mirror of right subtree
     * 4. Right child of new node = mirror of left subtree
     */
    return NULL;
}

void freeBinaryTree(BinaryTree *T) {
    /* TODO: Free all nodes in binary tree using postorder traversal
     * Algorithm:
     * 1. Free left subtree
     * 2. Free right subtree
     * 3. Free current node
     * 4. Set T to NULL
     */

    /* Algorithm: Same as BST - postorder traversal
    * 
    * Binary tree uses same structure as BST, just no ordering constraint
    * 
    * Base case: If tree is NULL, nothing to free
    * 
    * Recursive case:
    * 1. Free left subtree
    * 2. Free right subtree  
    * 3. Free current node
    * 4. Set *T to NULL
    * 
    * Implementation:
    */
    if (*T == NULL) return;

    freeBinaryTree(&((*T)->left));
    freeBinaryTree(&((*T)->right));

    free(*T);
    *T = NULL;
}
