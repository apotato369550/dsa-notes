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
void heapifyUp(HeapNode *insertHeapNode) ;
void heapifyDown(Root root);
HeapNode *findLastNode(Root root, int nodeCount);
void deleteLastNode(Root root, int nodeCount);
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
    heapifyUp(newHeapNode);
}

int extractMinimum(Root *root) {
    int minimum = (*root)->value;

    // get last node
    HeapNode *lastNode = findLastNode(root, getNodeCount(root));

    // swap values
    //delete last node

    // heapify down
    
    // return min
    return minimum;
}

int peekMinimum(Root *root) {
    return (*root)->value;
}

void heapifyUp(HeapNode *insertHeapNode) {
    // bubble the newly inserted node upward till
    // min-heap property is restored :V
    HeapNode *current = insertHeapNode;
    while (current->parent != NULL) {
        if (current->value < current->parent->value) {
            // perform swap
            int temp = current->value;
            current->value = current->parent->value;
            current->parent->value = temp;

            // "bubble up"
            current = current->parent;
        } else {
            // node is at where it needs to be :V
            break;
        }
    }
}

// next three functions are necessary for extractMinimum():
// heapifyDown, findLastNode, and deleteLastNode

void heapifyDown(Root root) {
    // sink the new root downward to its correct position in the heap.
    return;
}

HeapNode *findLastNode(Root root, int nodeCount) {
    return NULL;
}

void deleteLastNode(Root root, int nodeCount) {
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