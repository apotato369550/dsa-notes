#ifndef TREE
#define TREE

#define MAX_CHILDREN

typedef struct TreeNode {
    int data;
    int childCount;
    struct TreeNode* children[MAX_CHILDREN];
} *TreeNodePointer, *Tree, TreeNode;

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} *BinaryTreeNodePointer, *BinaryTree, BinaryTreeNode;

// create labeled trees, then make hamming code operations from them uwu

#endif