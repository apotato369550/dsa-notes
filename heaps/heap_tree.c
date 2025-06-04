#include <stdio.h>
#include <stdlib.h>

// figure out how to implement a minheap using tree/pointers

typedef struct HeapNode {
    int value;
    struct HeapNode *left;
    struct HeapNode *right;
    struct HeapNode *parent;
} HeapNode, *Root;

HeapNode *createNode(int value);
void printTabs(int tabs);
void printTree(Root root, int tabs);
HeapNode *findInsertionPoint(Root *root);
void insertNode(Root *root, int value);
int extractMinimum(Root *root);
int peekMinimum(Root *root);
void heapifyUp(Root *root);
void heapifyDown(Root *root);
int getNodeCount(Root *root);
void destroyHeap(Root *root);

// continue making function prototypes

int main() {
    return 0;
}

HeapNode *createNode(int value) {
    return NULL;
}

void printTabs(int tabs) {
    return;
}

void printTree(Root root, int tabs) {
    return;
}

HeapNode *findInsertionPoint(Root *root) {
    return NULL;
}

void insertNode(Root *root, int value) {
    return;
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

int getNodeCount(Root *root) {
    // something something recursive count
    return 0;
}

void destroyHeap(Root *root) {
    return;
}