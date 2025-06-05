#include <stdio.h>
#include <stdlib.h>

// figure out how to implement a minheap using tree/pointers

typedef struct HeapNode {
    int value;
    struct HeapNode *left;
    struct HeapNode *right;
    struct HeapNode *parent;
} HeapNode, *Root;

HeapNode *createHeapNode(int value, HeapNode *parent);
void printTabs(int tabs);
void printTree(Root root, int tabs);
HeapNode *findInsertionPoint(Root *root);
void insertHeapNode(Root *root, int value);
int extractMinimum(Root *root);
int peekMinimum(Root *root);
void heapifyUp(Root *root);
void heapifyDown(Root *root);
int getNodeCount(Root root);
void destroyHeap(Root *root);

// continue making function prototypes

int main() {
    return 0;
}

HeapNode *createHeapNode(int value, HeapNode *parent) {
    HeapNode *newHeapNode = malloc(sizeof(HeapNode));

    if (newHeapNode == NULL) {
        printf("Unable to allocate memory.\n");
        return NULL;
    }

    newHeapNode->value = value;
    newHeapNode->parent = parent;
    newHeapNode->left = NULL;
    newHeapNode->right = NULL;
    return newHeapNode;
}

void printTabs(int tabs) {
    for (int i = 0; i < tabs; i++) {
        printf("\t");
    }
}

void printTree(Root root, int tabs) {
    if (root == NULL) {
        printTabs(tabs);
        printf("--- EMPTY ---\n");
    } else {
        printTree(root->right, tabs + 1);
        printTabs(tabs);
        printf("%d\n", root->value);
        printTree(root->left, tabs + 1);
    }
}

HeapNode *findInsertionPoint(Root *root) {
    return NULL;
}

void insertHeapNode(Root *root, int value) {
    HeapNode *parent = findInsertionPoint(root);
    HeapNode *newHeapNode = createHeapNode(value, root);
    if (parent->left == NULL) {
        parent->left = newHeapNode;
    } else {
        parent->right = newHeapNode;
    }
}

int extractMinimum(Root *root) {
    int minimum = (*root)->value;
    // free root, heapify down or smth
    return minimum;
}

int peekMinimum(Root *root) {
    return (*root)->value;
}

void heapifyUp(Root *root) {
    return;
}

void heapifyDown(Root *root) {
    return; 
}

int getNodeCount(Root root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftCount = getNodeCount(root->left);
        int rightCount = getNodeCount(root->right);
        return 1 + leftCount + rightCount;
    }
}

void destroyHeap(Root *root) {
    return;
}