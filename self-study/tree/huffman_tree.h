#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// HUFFMAN TREE OPERATIONS (Based on Aho Section 3.4)
// ============================================================================
// Huffman coding: Optimal prefix codes using weighted binary trees
// Used for data compression

// ----------------------------------------------------------------------------
// Character-Frequency Pair (Input to Huffman Algorithm)
// ----------------------------------------------------------------------------

typedef struct {
    char character;
    double frequency;  // or probability weight
} CharFreq;

// ----------------------------------------------------------------------------
// Huffman Code Table (Output of Huffman Algorithm)
// ----------------------------------------------------------------------------

typedef struct {
    char character;
    char code[256];  // Binary code as string (e.g., "1011")
    int codeLength;
} HuffmanCode;

// ----------------------------------------------------------------------------
// Basic Huffman Tree Operations
// ----------------------------------------------------------------------------

// Initialize Huffman tree to empty
void initHuffmanTree(HuffmanTree *T);

// Create a leaf node for a character with given weight
HuffmanTreeNode* createHuffmanLeaf(char character, double weight);

// Create an interior node by merging two trees
HuffmanTreeNode* mergeHuffmanTrees(HuffmanTree left, HuffmanTree right);

// Get weight of a Huffman tree (sum of all leaf weights)
double getWeight(HuffmanTree T);

// Check if node is a leaf
bool isHuffmanLeaf(HuffmanTreeNode *n);

// ----------------------------------------------------------------------------
// Huffman Forest Operations (used during algorithm)
// ----------------------------------------------------------------------------

// Initialize empty forest
void initForest(HuffmanForest *F);

// Add a tree to the forest
void addToForest(HuffmanForest *F, HuffmanTree T);

// Find and remove the two trees with smallest weights from forest
// Returns them through the parameters
void extractTwoLightest(HuffmanForest *F, HuffmanTree *lightest, HuffmanTree *secondLightest);

// Get number of trees in forest
int forestSize(HuffmanForest F);

// Check if forest is empty
bool isForestEmpty(HuffmanForest F);

// ----------------------------------------------------------------------------
// Huffman Algorithm (from Aho Section 3.4)
// ----------------------------------------------------------------------------

// Build Huffman tree from array of character frequencies
// This is the main Huffman algorithm
HuffmanTree buildHuffmanTree(CharFreq *charFreqs, int numChars);

// Extract Huffman codes from the tree
// Stores codes in the provided array (must be pre-allocated)
void extractCodes(HuffmanTree T, HuffmanCode *codes, int *numCodes);

// ----------------------------------------------------------------------------
// Encoding and Decoding
// ----------------------------------------------------------------------------

// Encode a string using Huffman codes
char* encode(char *text, HuffmanCode *codes, int numCodes);

// Decode a binary string using Huffman tree
char* decode(char *encoded, HuffmanTree T);

// ----------------------------------------------------------------------------
// Display and Utility Operations
// ----------------------------------------------------------------------------

// Display Huffman tree structure with weights
void displayHuffmanTree(HuffmanTree T);

// Display code table
void displayCodeTable(HuffmanCode *codes, int numCodes);

// Calculate average code length (weighted by frequencies)
double averageCodeLength(HuffmanCode *codes, CharFreq *freqs, int numChars);

// Calculate compression ratio
double compressionRatio(char *original, char *encoded);

// Verify that codes form a valid prefix code (no code is prefix of another)
bool isValidPrefixCode(HuffmanCode *codes, int numCodes);

// ----------------------------------------------------------------------------
// Tree Properties
// ----------------------------------------------------------------------------

// Count total nodes in Huffman tree
int countHuffmanNodes(HuffmanTree T);

// Calculate height of Huffman tree
int huffmanTreeHeight(HuffmanTree T);

// Count leaf nodes (characters)
int countHuffmanLeaves(HuffmanTree T);

// Check if tree is empty
bool isHuffmanTreeEmpty(HuffmanTree T);

// ----------------------------------------------------------------------------
// Memory Management
// ----------------------------------------------------------------------------

// Free Huffman tree
void freeHuffmanTree(HuffmanTree *T);

// Free forest
void freeForest(HuffmanForest *F);

#endif
