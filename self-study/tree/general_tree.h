#ifndef GENERAL_TREE_H
#define GENERAL_TREE_H

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// GENERAL TREE OPERATIONS (Based on Aho Section 3.2)
// ============================================================================

// ----------------------------------------------------------------------------
// Basic ADT Operations from Aho
// ----------------------------------------------------------------------------

// Initialize tree to null/empty
void initTree(GeneralTree *T);

// ROOT(T) - Returns root node of tree T (NULL if empty)
GeneralTreeNode* root(GeneralTree T);

// PARENT(n, T) - Returns parent of node n (NULL if n is root)
GeneralTreeNode* parent(GeneralTreeNode *n);

// LEFTMOST_CHILD(n, T) - Returns leftmost child of node n (NULL if leaf)
GeneralTreeNode* leftmostChild(GeneralTreeNode *n);

// RIGHT_SIBLING(n, T) - Returns right sibling of node n (NULL if rightmost)
GeneralTreeNode* rightSibling(GeneralTreeNode *n);

// LABEL(n, T) - Returns the label stored at node n
char getLabel(GeneralTreeNode *n);

// MAKENULL(T) - Makes T the null tree
void makeNull(GeneralTree *T);

// ----------------------------------------------------------------------------
// Tree Construction Operations
// ----------------------------------------------------------------------------

// CREATE(v, label, numChildren, children...) - Creates a new tree
// Note: In practice, we'll build trees incrementally rather than all at once
GeneralTreeNode* createNode(int data, char label);

// Add a child to a node (attaches newChild as rightmost child of parent)
void addChild(GeneralTreeNode *parent, GeneralTreeNode *newChild);

// Create root with given value and label
void createRoot(GeneralTree *T, int data, char label);

// ----------------------------------------------------------------------------
// Tree Traversal Operations (for testing and display)
// ----------------------------------------------------------------------------

// Preorder traversal - Visit node, then children left to right
void preorder(GeneralTree T);

// Postorder traversal - Visit children left to right, then node
void postorder(GeneralTree T);

// Level-order (breadth-first) traversal
void levelOrder(GeneralTree T);

// Display tree structure (indented representation)
void displayTree(GeneralTree T);

// ----------------------------------------------------------------------------
// Additional Utility Operations
// ----------------------------------------------------------------------------

// Count total nodes in tree
int countNodes(GeneralTree T);

// Calculate height of tree (number of edges on longest path from root to leaf)
int height(GeneralTree T);

// Count number of children of a node
int childCount(GeneralTreeNode *n);

// Check if tree is empty
bool isEmpty(GeneralTree T);

// Check if node is a leaf
bool isLeaf(GeneralTreeNode *n);

// Check if node is root
bool isRoot(GeneralTreeNode *n, GeneralTree T);

// ----------------------------------------------------------------------------
// Advanced Operations from Aho Section 3.6
// ----------------------------------------------------------------------------

// Compute number of proper descendants of node n
int descendantCount(GeneralTreeNode *n);

// Assign postorder numbers to all nodes
void assignPostorder(GeneralTree T, int *postorderArray, int *index);

// Test if node x is a descendant of node y using postorder numbering
bool isDescendant(GeneralTreeNode *x, GeneralTreeNode *y, int *postorder, int *desc);

#endif
