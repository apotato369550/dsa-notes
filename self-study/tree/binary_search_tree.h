#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ============================================================================
// BINARY SEARCH TREE OPERATIONS (Based on Aho Section 5.1)
// ============================================================================
// BST Property: For every node x:
//   - All elements in left subtree < element at x
//   - All elements in right subtree > element at x

// ----------------------------------------------------------------------------
// Basic ADT Operations from Aho
// ----------------------------------------------------------------------------

// Initialize BST to empty
void initBST(BST *T);

// MAKENULL(A) - Makes A the empty set
void makeNullBST(BST *T);

// MEMBER(x, A) - Tests if element x is in set A
bool member(BST T, int x);

// INSERT(x, A) - Adds element x to set A
void insert(BST *T, int x);

// DELETE(x, A) - Removes element x from set A
void deleteElement(BST *T, int x);

// MIN(A) - Returns the smallest element in set A
int min(BST T);

// MAX(A) - Returns the largest element (not in book, but standard)
int max(BST T);

// DELETEMIN(A) - Removes and returns smallest element from A
int deleteMin(BST *T);

// DELETEMAX(A) - Removes and returns largest element (mirror of deleteMin)
int deleteMax(BST *T);

// ----------------------------------------------------------------------------
// BST Navigation Operations
// ----------------------------------------------------------------------------

// Find node containing value x (returns pointer to node or NULL)
BSTNode* findBSTNode(BST T, int x);

// Find minimum node in tree (returns pointer)
BSTNode* findMinNode(BST T);

// Find maximum node in tree (returns pointer)
BSTNode* findMaxNode(BST T);

// Find inorder successor of a node
BSTNode* successor(BST T, BSTNode *n);

// Find inorder predecessor of a node
BSTNode* predecessor(BST T, BSTNode *n);

// ----------------------------------------------------------------------------
// Tree Traversal Operations
// ----------------------------------------------------------------------------

// Inorder traversal (prints elements in sorted order for BST!)
void inorderBST(BST T);

// Preorder traversal
void preorderBST(BST T);

// Postorder traversal
void postorderBST(BST T);

// Display tree structure
void displayBST(BST T);

// ----------------------------------------------------------------------------
// Tree Properties and Utilities
// ----------------------------------------------------------------------------

// Check if tree is empty
bool isBSTEmpty(BST T);

// Count total nodes in BST
int countBSTNodes(BST T);

// Calculate height of BST
int bstHeight(BST T);

// Check if tree is a valid BST (useful for testing)
bool isValidBST(BST T, int minValue, int maxValue);

// Count nodes in a given range [min, max]
int countInRange(BST T, int minVal, int maxVal);

// ----------------------------------------------------------------------------
// Advanced BST Operations
// ----------------------------------------------------------------------------

// Build a BST from sorted array (creates balanced tree)
BST buildFromSortedArray(int *arr, int size);

// Find kth smallest element (1-indexed)
int kthSmallest(BST T, int k);

// Find kth largest element (1-indexed)
int kthLargest(BST T, int k);

// Get all elements in range [min, max] in sorted order
void rangeQuery(BST T, int minVal, int maxVal);

// Calculate sum of all elements
int sumBST(BST T);

// Free all nodes in BST
void freeBST(BST *T);

#endif
