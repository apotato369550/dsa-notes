#include "huffman_tree.h"

// ============================================================================
// Basic Huffman Tree Operations
// ============================================================================

void initHuffmanTree(HuffmanTree *T) {
    /* TODO: Initialize Huffman tree to NULL */
}

HuffmanTreeNode* createHuffmanLeaf(char character, double weight) {
    /* TODO: Create a leaf node for a character
     * Set character, weight, isLeaf = true
     * Set left and right to NULL
     */
    return NULL;
}

HuffmanTreeNode* mergeHuffmanTrees(HuffmanTree left, HuffmanTree right) {
    /* TODO: Create interior node by merging two trees
     * Algorithm (from Aho Section 3.4):
     * 1. Create new node
     * 2. Set left child = left tree
     * 3. Set right child = right tree
     * 4. Set weight = weight(left) + weight(right)
     * 5. Set isLeaf = false
     * 6. character field is not meaningful for interior nodes
     */
    return NULL;
}

double getWeight(HuffmanTree T) {
    /* TODO: Return weight of tree
     * If tree is NULL, return 0
     * Otherwise, return T->weight
     */
    return 0.0;
}

bool isHuffmanLeaf(HuffmanTreeNode *n) {
    /* TODO: Check if node is a leaf
     * Return n->isLeaf
     */
    return false;
}

// ============================================================================
// Huffman Forest Operations
// ============================================================================

void initForest(HuffmanForest *F) {
    /* TODO: Initialize forest to NULL (empty linked list) */
}

void addToForest(HuffmanForest *F, HuffmanTree T) {
    /* TODO: Add tree T to forest
     * Create new forest node containing T
     * Insert into linked list (can insert at front for simplicity)
     */
}

void extractTwoLightest(HuffmanForest *F, HuffmanTree *lightest, HuffmanTree *secondLightest) {
    /* TODO: Find and remove two trees with smallest weights
     * Algorithm (from Aho Section 3.4):
     * 1. Traverse forest to find tree with minimum weight
     * 2. Remove it from forest, store in lightest
     * 3. Traverse again to find new minimum
     * 4. Remove it, store in secondLightest
     *
     * More efficient: traverse once, tracking two minimums
     */
}

int forestSize(HuffmanForest F) {
    /* TODO: Count number of trees in forest
     * Traverse linked list and count nodes
     */
    return 0;
}

bool isForestEmpty(HuffmanForest F) {
    /* TODO: Check if forest is empty */
    return true;
}

// ============================================================================
// Huffman Algorithm
// ============================================================================

HuffmanTree buildHuffmanTree(CharFreq *charFreqs, int numChars) {
    /* TODO: Build Huffman tree using Huffman's algorithm
     * Algorithm (from Aho Section 3.4):
     *
     * 1. Create a forest of single-node trees, one for each character
     *    Each tree is a leaf with the character and its frequency
     *
     * 2. While forest has more than one tree:
     *    a. Find two trees with smallest weights (use extractTwoLightest)
     *    b. Merge them into new tree with weight = sum of their weights
     *    c. Add merged tree back to forest
     *
     * 3. The remaining tree is the Huffman tree
     *
     * Example:
     * Characters: A(0.4), B(0.3), C(0.2), D(0.1)
     * Initial forest: [A:0.4] [B:0.3] [C:0.2] [D:0.1]
     *
     * Step 1: Merge D and C (smallest)
     * Forest: [A:0.4] [B:0.3] [DC:0.3]
     *
     * Step 2: Merge B and DC (both 0.3, pick either)
     * Forest: [A:0.4] [BDC:0.6]
     *
     * Step 3: Merge A and BDC
     * Final tree: [ABDC:1.0]
     */
    return NULL;
}

void extractCodes(HuffmanTree T, HuffmanCode *codes, int *numCodes) {
    /* TODO: Extract Huffman codes by traversing the tree
     * Algorithm:
     * 1. Use recursive helper function that builds code string as it goes
     * 2. At each node:
     *    - If going left, append '0' to current code
     *    - If going right, append '1' to current code
     * 3. When reaching a leaf, store the character and its code
     *
     * Helper function signature:
     * void extractCodesHelper(HuffmanTree T, char *currentCode, int depth,
     *                         HuffmanCode *codes, int *numCodes)
     */
}

// ============================================================================
// Encoding and Decoding
// ============================================================================

char* encode(char *text, HuffmanCode *codes, int numCodes) {
    /* TODO: Encode text using Huffman codes
     * Algorithm:
     * 1. Allocate string for encoded result
     * 2. For each character in text:
     *    - Find its code in the codes array
     *    - Append the code to result
     * 3. Return result
     */
    return NULL;
}

char* decode(char *encoded, HuffmanTree T) {
    /* TODO: Decode binary string using Huffman tree
     * Algorithm:
     * 1. Start at root of tree
     * 2. For each bit in encoded string:
     *    - If '0', go left
     *    - If '1', go right
     *    - If reach leaf, output character and reset to root
     * 3. Return decoded string
     */
    return NULL;
}

// ============================================================================
// Display and Utility Operations
// ============================================================================

void displayHuffmanTree(HuffmanTree T) {
    /* TODO: Display Huffman tree with weights
     * Show structure with characters at leaves and weights at all nodes
     */
}

void displayCodeTable(HuffmanCode *codes, int numCodes) {
    /* TODO: Display table of characters and their codes
     * Format:
     * Character | Code    | Length
     * --------- | ------- | ------
     * A         | 0       | 1
     * B         | 10      | 2
     * C         | 110     | 3
     * D         | 111     | 3
     */
}

double averageCodeLength(HuffmanCode *codes, CharFreq *freqs, int numChars) {
    /* TODO: Calculate average code length weighted by frequencies
     * Formula: sum(frequency[i] * codeLength[i]) for all characters
     * This measures compression effectiveness
     */
    return 0.0;
}

double compressionRatio(char *original, char *encoded) {
    /* TODO: Calculate compression ratio
     * Ratio = (original size in bits) / (encoded size in bits)
     * Assuming original uses 8 bits per character
     * Encoded size = length of encoded binary string
     */
    return 0.0;
}

bool isValidPrefixCode(HuffmanCode *codes, int numCodes) {
    /* TODO: Verify codes form valid prefix code
     * A prefix code: no code is a prefix of another
     * Algorithm:
     * For each pair of codes (i, j):
     *   Check if codes[i] is a prefix of codes[j] or vice versa
     *   If yes, return false
     * Return true
     */
    return false;
}

// ============================================================================
// Tree Properties
// ============================================================================

int countHuffmanNodes(HuffmanTree T) {
    /* TODO: Count total nodes (leaves + interior nodes) */
    return 0;
}

int huffmanTreeHeight(HuffmanTree T) {
    /* TODO: Calculate height of tree */
    return -1;
}

int countHuffmanLeaves(HuffmanTree T) {
    /* TODO: Count leaf nodes (characters)
     * For Huffman tree with n characters, there are exactly n leaves
     * and n-1 interior nodes (for a total of 2n-1 nodes)
     */
    return 0;
}

bool isHuffmanTreeEmpty(HuffmanTree T) {
    /* TODO: Check if tree is empty */
    return true;
}

// ============================================================================
// Memory Management
// ============================================================================

void freeHuffmanTree(HuffmanTree *T) {
    /* TODO: Free all nodes in Huffman tree using postorder traversal */
}

void freeForest(HuffmanForest *F) {
    /* TODO: Free all nodes in forest
     * 1. Free each tree in the forest
     * 2. Free the forest list nodes
     */
}
