#ifndef TREE
#define TREE

typedef struct TreeNode {
    int data;
    struct TreeNode** children;
} *TreeNodePointer, *Tree, TreeNode;

typedef struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} *BinaryTreeNodePointer, *BinaryTree, BinaryTreeNode;

#endif