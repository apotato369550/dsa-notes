#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

// Common label type for nodes that need labels (expression trees, Huffman trees, etc.)
#define NO_LABEL '\0'

// ============================================================================
// GENERAL TREE TYPE DEFINITIONS
// ============================================================================
// Based on Aho Section 3.2 - General trees with variable number of children
// Uses leftmost-child, right-sibling representation

typedef struct GeneralTreeNode {
    int data;                              // Value stored in node
    char label;                             // Optional label for the node
    struct GeneralTreeNode *leftmostChild;  // Pointer to first child
    struct GeneralTreeNode *rightSibling;   // Pointer to next sibling
    struct GeneralTreeNode *parent;         // Pointer to parent (for PARENT operation)
} GeneralTreeNode, *GeneralTree;

// ============================================================================
// BINARY TREE TYPE DEFINITIONS
// ============================================================================
// Standard binary tree - each node has at most two children

typedef struct BinaryTreeNode {
    int data;                          // Value stored in node
    char label;                        // Optional label for the node
    struct BinaryTreeNode *left;       // Left child
    struct BinaryTreeNode *right;      // Right child
    struct BinaryTreeNode *parent;     // Parent pointer (optional, for easier traversal)
} BinaryTreeNode, *BinaryTree;

// ============================================================================
// BINARY SEARCH TREE TYPE DEFINITIONS
// ============================================================================
// Binary tree with ordering property: left < node < right
// Uses same structure as BinaryTree but with different operations

typedef BinaryTreeNode BSTNode;
typedef BinaryTree BST;

// ============================================================================
// EXPRESSION TREE TYPE DEFINITIONS
// ============================================================================
// Binary tree for representing arithmetic expressions
// Leaves = operands (numbers), Interior nodes = operators

typedef struct ExprTreeNode {
    bool isOperator;                     // true if operator, false if operand
    union {
        char op;                         // Operator: +, -, *, /
        double value;                    // Operand: numeric value
    } content;
    struct ExprTreeNode *left;           // Left operand/subtree
    struct ExprTreeNode *right;          // Right operand/subtree
} ExprTreeNode, *ExprTree;

// ============================================================================
// HUFFMAN TREE TYPE DEFINITIONS
// ============================================================================
// Binary tree for Huffman coding (weighted trees)
// Leaves contain characters, interior nodes are merge points

typedef struct HuffmanTreeNode {
    char character;                      // Character (only meaningful for leaves)
    double weight;                       // Frequency/probability weight
    bool isLeaf;                         // true if leaf node
    struct HuffmanTreeNode *left;        // Left child (0 in code)
    struct HuffmanTreeNode *right;       // Right child (1 in code)
} HuffmanTreeNode, *HuffmanTree;

// ============================================================================
// HELPER TYPE FOR HUFFMAN FOREST
// ============================================================================
// Used during Huffman algorithm to manage multiple trees

typedef struct HuffmanForestNode {
    HuffmanTree tree;
    struct HuffmanForestNode *next;
} HuffmanForestNode, *HuffmanForest;

#endif
