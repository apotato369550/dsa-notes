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

// continue making function prototypes

int main() {
    return 0;
}