#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUMBER_NOT_FOUND INT_MIN

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createTreeNode(int value);
void printIndentation(int indents);
void printTree(TreeNode *root, int indents);
int insertNumber(TreeNode **root, int value);
int findNumber(TreeNode *root, int value);

int main() {
    TreeNode *root = createTreeNode(15);

    insertNumber(&root, 5);
    insertNumber(&root, 10);
    insertNumber(&root, 20);
    insertNumber(&root, 25);
    insertNumber(&root, 16);
    insertNumber(&root, 7);

    printTree(root, 0);


    return 0;
}

TreeNode *createTreeNode(int value) {
    TreeNode *newTreeNode = malloc(sizeof(TreeNode));
    if (newTreeNode) {
        newTreeNode->value = value;
        newTreeNode->left = NULL;
        newTreeNode->right = NULL;
    }

    return newTreeNode;
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

int insertNumber(TreeNode **root, int value) {
    if (*root == NULL) {
        *root = createTreeNode(value);
        return 1;
    } else {
        if (value < (*root)->value) {
            insertNumber(&(*root)->left, value);
        } else {
            insertNumber(&(*root)->right, value);
        }
    }

    return 0;
}

int findNumber(TreeNode *root, int value) {
    if (root == NULL) {
        return 0;
    }

    if (root->value == value) {
        return 1;
    } else if (value < root->value) {
        findNumber(root->left, value);
    } else {
        findNumber(root->right, value);
    }

    return 0;
}