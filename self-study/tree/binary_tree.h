#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// BINARY TREE OPERATIONS
// ============================================================================
// Standard binary tree operations - no ordering constraints
// Each node has at most two children (left and right)

// ----------------------------------------------------------------------------
// Basic Operations
// ----------------------------------------------------------------------------

// Initialize binary tree to empty
void initBinaryTree(BinaryTree *T);

// Create a new node with given data and label
BinaryTreeNode* createBinaryNode(int data, char label);

// Create root node for tree
void createBinaryRoot(BinaryTree *T, int data, char label);

// LEFTCHILD(n) - Returns left child of node n (NULL if none)
BinaryTreeNode* leftChild(BinaryTreeNode *n);

// RIGHTCHILD(n) - Returns right child of node n (NULL if none)
BinaryTreeNode* rightChild(BinaryTreeNode *n);

// PARENT(n) - Returns parent of node n (NULL if root)
BinaryTreeNode* binaryParent(BinaryTreeNode *n);

// Check if node is NULL
bool isNull(BinaryTreeNode *n);

// ----------------------------------------------------------------------------
// Tree Construction Operations
// ----------------------------------------------------------------------------

// Set left child of parent to newChild
void setLeftChild(BinaryTreeNode *parent, BinaryTreeNode *newChild);

// Set right child of parent to newChild
void setRightChild(BinaryTreeNode *parent, BinaryTreeNode *newChild);

// Build a sample binary tree for testing
BinaryTree buildSampleBinaryTree();

// ----------------------------------------------------------------------------
// Tree Traversal Operations
// ----------------------------------------------------------------------------

// Preorder traversal (Node -> Left -> Right)
void preorderBinary(BinaryTree T);

// Inorder traversal (Left -> Node -> Right)
void inorderBinary(BinaryTree T);

// Postorder traversal (Left -> Right -> Node)
void postorderBinary(BinaryTree T);

// Level-order (breadth-first) traversal
void levelOrderBinary(BinaryTree T);

// Display tree structure (visual representation)
void displayBinaryTree(BinaryTree T);

// ----------------------------------------------------------------------------
// Tree Properties and Utilities
// ----------------------------------------------------------------------------

// Count total nodes in binary tree
int countBinaryNodes(BinaryTree T);

// Calculate height of binary tree
int binaryHeight(BinaryTree T);

// Check if binary tree is empty
bool isBinaryEmpty(BinaryTree T);

// Check if node is a leaf
bool isBinaryLeaf(BinaryTreeNode *n);

// Count leaf nodes in tree
int countLeaves(BinaryTree T);

// Check if tree is a full binary tree (every node has 0 or 2 children)
bool isFullBinaryTree(BinaryTree T);

// Check if tree is a complete binary tree
bool isCompleteBinaryTree(BinaryTree T);

// ----------------------------------------------------------------------------
// Advanced Operations
// ----------------------------------------------------------------------------

// Find a node with given data (returns first occurrence)
BinaryTreeNode* findNode(BinaryTree T, int data);

// Get level of a node (root is at level 0)
int getNodeLevel(BinaryTree T, BinaryTreeNode *target);

// Check if two trees are structurally identical
bool areIdentical(BinaryTree T1, BinaryTree T2);

// Create a mirror/reflection of the tree
BinaryTree mirrorTree(BinaryTree T);

// Free all nodes in binary tree
void freeBinaryTree(BinaryTree *T);

#endif
