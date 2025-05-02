#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createTreeNode(int value);
void printIndentation(int indents);
void printTree(TreeNode *root, int indents);

int main() {
    TreeNode *node1 = createTreeNode(1);
    TreeNode *node2 = createTreeNode(2);
    TreeNode *node3 = createTreeNode(3);
    TreeNode *node4 = createTreeNode(4);
    TreeNode *node5 = createTreeNode(5);

    node1->left = node2;
    node1->right = node3;
    node3->left = node4;
    node3->right = node5;

    printTree(node1, 0);

    return 0;
}

TreeNode *createTreeNode(int value) {
    TreeNode *newNode = malloc(sizeof(TreeNode));
    if (newNode) {
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }

    return newNode;
}

void printIndentation(int value) {
    for (int i = 0; i < value; i++) {
        printf("\t");
    }
}

void printTree(TreeNode *root, int indents) {
    if (root == NULL) {
        printIndentation(indents);
        printf("--- EMPTY ---\n");
    } else {
        printTree(root->left, indents + 1);
        printIndentation(indents);
        printf("%d \n", root->value);
        printTree(root->right, indents + 1);
    }
}