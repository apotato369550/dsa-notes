#include "binary_search_tree.h"

void insertNode(BinaryTreeNodePointer *root, int data) {
    BinaryTreeNode *newNode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    if (newNode == NULL) return;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    BinaryTreeNodePointer *trav = &root;
    // if data is greater than current/trav
    // else
    if ((*root) == NULL) {
        *root = newNode;
        return;
    }
    // trav = ((*trav)->data > data ? &(*trav)->left : &(*trav)->right)
    //

    BinaryTreeNodePointer *trav = &root;
    for (trav; (*trav) != NULL; trav = ((*trav)->data > data ? &(*trav)->left : &(*trav)->right)) {}
    *trav = newNode;
}

void deleteNode(BinaryTreeNodePointer *root, int data) {
    if (!isMember(root, data)) return;
    BinaryTreeNodePointer *trav = &root;
    for (trav; (*trav) != NULL && (*trav)->data != data; trav = ((*trav)->data > data ? &(*trav)->left : &(*trav)->right)) {}
    BinaryTreeNodePointer *temp = trav;
    if ((*temp)->left == NULL && (*temp)->right == NULL) {
        free(*temp);
        *temp = NULL;
    } else if((*temp)->left == NULL || (*temp)->right == NULL) {
        if ((*temp)->left == NULL) {
            (*trav) = (*temp)->right;
            free(temp);
        } else {
            (*trav) = (*temp)->left;
            free(temp);
        }
    } else {
        // something about immediate predecessor or successor idk. 
        // how do we tell if we're in the left or the right?
        // by comparing it to data
        return;
    }
}

bool isMember(BinaryTreeNodePointer *root, int data) {
    BinaryTreeNodePointer *trav = &root;
    for (trav; (*trav) != NULL && (*trav)->data != data; trav = ((*trav)->data > data ? &(*trav)->left : &(*trav)->right)) {}
    return trav != NULL;
}

int getMin(BinaryTreeNodePointer root) {
    return;
}

int getMax(BinaryTreeNodePointer root) {
    return;
}