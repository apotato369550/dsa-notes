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
    HeapNode *value;
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
void heapifyUp(HeapNode *heapNode) ;
void heapifyDown(Root root);

// queue helper functions
void initializeQueue(Queue *queue);
void enqueue(Queue *queue, HeapNode *heapNode);
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
void heapifyUp(HeapNode *heapNode) {
    // bubble the newly inserted node upward till
    // min-heap property is restored :V
    while (heapNode->parent != NULL) {
        if (heapNode->value < heapNode->parent->value) {
            // perform swap
            int temp = heapNode->value;
            heapNode->value = heapNode->parent->value;
            heapNode->parent->value = temp;

            // "bubble up"
            heapNode = heapNode->parent;
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
    while (root->left != NULL || root->right != NULL) {
        // identify the smaller child (min of left/right)
        int isLeftSmaller = 1;
        HeapNode *min = root->left;
        if (root->left->value > root->right->value) {
            int isLeftSmaller = 0;
        } 
    }

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

void enqueue(Queue *queue, HeapNode *heapNode) {
    // follow enqueue logic from bstmania

    // create new queuenode and set its value to heapnode and its next to null
    QueueNode *newQueueNode = malloc(sizeof(QueueNode));
    newQueueNode->next = heapNode;
    newQueueNode->next = NULL;

    // if tail is not null, append to tail's next
    if (queue->tail != NULL) {
        queue->tail = queue->tail->next;
    }

    // move tail pointer to point to the new node, which is now at tail
    queue->tail = queue->tail->next;

    // if queue's head is null, set head to the newnode
    // this is for if queue was empty, then we added a new, first node
    if (queue->head == NULL) {
        queue->head = newQueueNode;
    }
}

HeapNode *dequeue(Queue *queue) {
    // follow dequeue logic from bstmania

    // if queue's head is null, return null
    if (queue->head == NULL) {
        return NULL;
    }

    // set a temp variable pointing to head
    QueueNode *temp = queue->head;

    // move head to head->next
    queue->head = queue->head->next;

    // set a heapnode with value equal to temp's value
    HeapNode *dequeuedNode = temp->value;

    // free temp
    free(temp);

    // if head is null, set tail to null. queue is empty
    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    // return the treenode
    return dequeuedNode;
}


HeapNode *findLastNode(Root root) {
    // declare an queue
    Queue queue;
    initializeQueue(&queue);
    // enqueue root
    enqueue(&queue, root);

    // declare a lastNode variable and set it to null intially
    HeapNode *lastNode = NULL;

    // loop through while queue's head is not null
    while (queue.head != NULL) {
        // dequeue a queuenode
        lastNode = dequeue(&queue);

        // enqueue left
        if (lastNode->left != NULL) {
            enqueue(&queue, lastNode->left);
        }   
        // enqeue right
        if (lastNode->right != NULL) {
            enqueue(&queue, lastNode->right);
        }   
    }

    // return the lastNode variable's value
    return lastNode;
}

void deleteLastNode(Root root) {
    // call findLastNode()
    HeapNode *lastNode = findLastNode(root);

    // set temp pointer variable equal to the lastNode's parent
    HeapNode *temp = lastNode->parent;

    // determine if last node is left or right child: temp->left == lastNode, then set left = null, otherwise set right to null
    if (temp->left == lastNode) {
        temp->left = NULL;
    } else {
        temp->right = NULL;
    }

    // free the last node
    free(lastNode);
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