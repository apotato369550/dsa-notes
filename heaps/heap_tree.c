#include <stdio.h>
#include <stdlib.h>

// figure out how to implement a minheap using tree/pointers

typedef struct HeapNode {
    int value;
    struct HeapNode *left;
    struct HeapNode *right;
    struct HeapNode *parent;
} HeapNode, *Root;

typedef struct QueueNode {
    HeapNode *queueNode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *head;
    QueueNode *tail;
} Queue;

HeapNode *createHeapNode(int value, HeapNode *parent);
void printTabs(int tabs);
void printTree(Root root, int tabs);
HeapNode *findInsertionPoint(Root root);
void insertHeapNode(Root *root, int value);
int extractMinimum(Root *root);
int peekMinimum(Root root);
void heapifyUp(HeapNode *insertHeapNode) ;
void heapifyDown(Root root);

// queue helper functions
void initializeQueue(Queue *queue);
void enqueue(Queue *queue, HeapNode *queueNode);
HeapNode *dequeue(Queue *queue);

HeapNode *findLastNode(Root root);
void deleteLastNode(Root root);


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

HeapNode *findInsertionPoint(Root root) {
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

    // handle test case if root is the only node in the heap
    if ((*root)->left == NULL && (*root)->right == NULL) {
        free(*root);
        *root = NULL;
        return minimum;
    }

    // get last node
    HeapNode *lastNode = findLastNode(root);

    // swap values
    int temp = minimum;
    (*root)->value = lastNode->value;
    lastNode->value = temp;

    //delete last node
    deleteLastNode((*root));

    // heapify down
    heapifyDown((*root));

    // return min
    return minimum;
}

int peekMinimum(Root root) {
    if (root != NULL) {
        return root->value;
    } else {
        return -1;
    }
}


// maybe refactor this VVV
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
    // goal:
    // sink the new root downward to its correct position in the heap.

    // while the current node (root) still has at least one child
        // identify the smaller child (min of left/right)
        // compare parent's value with child's value
        // if child < parent, swap
        // move current pointer to child, and repeat
        // stop when node is smaller than both children 
        // stop also when both children are null
        // if only one child, compare with child. swap if necessary
    return;
}

void initializeQueue(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

void enqueue(Queue *queue, HeapNode *queueNode) {
    // follow enqueue logic from bstmania
    return;
}

HeapNode *dequeue(Queue *queue) {
    // follow dequeue logic from bstmania
    return NULL;
}


HeapNode *findLastNode(Root root) {
    // declare an queue
    // initialize said empty queue
    // while the queue is not empty,
        // dequeue a node
        // if it has a left child, enqueue it
        // if it has a right child, enqueue it as well
    // the last node dequeued is your last node. return its pointer
    return NULL;
}

void deleteLastNode(Root root) {
    // call findLastNode()
    // set temp pointer variable equal to the lastNode's parent
    // determine if last node is left or right child: temp->left == lastNode, then set left = null, otherwise set right to null
    // free the last node
    // set parent's left or right node to null
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