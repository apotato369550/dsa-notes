#include "general_tree.h"

void initialize(Tree *root) {
    *root = NULL;
}

void printPreOrder(Tree root) {
    if (root == NULL) return;

    printf("%d", root->data);
    for (int i = 0; i < root->childCount; printPreOrder(root->children[i]), i++) {}

}

void printPostOrder(Tree root) {
    if (root == NULL) return;
    for (int i = 0; i < root->childCount; printPreOrder(root->children[i]), i++) {}
    printf("%d", root->data);
}

void printInOrder(Tree root) {
    if (root == NULL) return;
    if (root->children[0] != NULL) printInOrder(root->children[0]);
    printf("%d", root->data);
    for (int i = 1; i < root->childCount; printPreOrder(root->children[i]), i++) {}
}

bool isMember(Tree root, int data) {
    // perform traditional traversal :VVV
    // tldr; dfs
    // any traversal does it, but inorder works best ig
    if (root == NULL) return false;
    if (root->children[0] != NULL) isMember(root->children[0], data);
    int i;
    for (i = 1; i < root->childCount && root->children[i]->data != data; isMember(root->children[i], data), i++) {}
    // if we ever break from the for loop, we know that it was found because
    // of the balaod of 2 cond traversal circa mam pena
    if (i != root->childCount) return true; 
    return root->data == data;
}

void insertNode(Tree *root, int data) {
    return; 
}

void deleteNode(Tree *root, int data) {
    return;
}

int getMin(Tree root) {
    return; 
}

int getMax(Tree root) {
    return;
}