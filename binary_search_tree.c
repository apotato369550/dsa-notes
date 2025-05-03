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