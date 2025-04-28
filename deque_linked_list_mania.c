#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DEQUE_EMPTY INT_MIN

// array implementation of a deque
// todo:
// node struct - basic node struct for lls
typedef struct Node {
    int value;
    struct Node *next;
} Node, *NodePointer;



// dequeue struct - stores head, tail of deque
typedef struct Deque {
    NodePointer head;
    NodePointer tail;
} Deque;

// selection menu - user selects stuff

// function prototypes
// initialize - sets head and tail to null
void initializeDeque(Deque *deque);

// display - display all values in deque
void displayDeque(Deque deque);

// put - places a node/inserts an item at the end of the deque
void put(Deque *deque, int value);

// dequeue - removes and returns the item at the head of the deque
int dequeue(Deque *deque);

// pop - removes an item from the tail of the queue
int pop(Deque *deque);

// things to look out for:
// when head and tail overlap
// when to move the pointers and stuff

int main () {
    int input = -1;
    Deque deque;
    initializeDeque(&deque);
    printf("Welcome to deque array mania! Where values are popped fresh from the vine!\n");
    while (input != 0) {
        printf("Please select from the following choices to proceed: \n");
        printf("0 - Exit\n");
        printf("1 - Display all items in deque\n");
        printf("2 - Put an item into the deque\n");
        printf("3 - Dequeue/remove an item from the head of the deque\n");
        printf("4 - Pop/remove an item from the tail of the deque \n");
        printf("Please select an option: ");
        scanf("%d", &input);

        switch(input) {
            case 0:
                printf("See you next time! :)) \n");
                break;
            case 1:
                printf("Displaying all items in deque...\n");
                displayDeque(deque);
                break;
            case 2:
                printf("Putting an item into the deque... \n");
                int value = 0;
                printf("Please enter value to put: ");
                scanf("%d", &value);
                put(&deque, value);
                break;
            case 3:
                printf("Dequeueing an item from the deque... \n");
                int dequeued = dequeue(&deque);
                if (dequeued != DEQUE_EMPTY) {
                    printf("Dequeued value: %d\n", dequeued);
                }
                break;
            case 4:
                printf("Popping an item from the deque...\n");
                int popped = pop(&deque);
                if (popped != DEQUE_EMPTY) {
                    printf("Popped value: %d\n", popped);
                }
                break;
            default:
                printf("Please enter a valid option...\n");
        }
    }
    return 0;
}

// initialize - sets head and tail to null
void initializeDeque(Deque *deque) {
    deque->head = NULL;
    deque->tail = NULL;
}

// display - display all values in deque
void displayDeque(Deque deque) {
    NodePointer temp = deque.head;
    printf("--- START OF DEQUE ---");
    while (temp != NULL) {
        printf("%d\n", temp->value);
    }
    printf("--- END OF DEQUE ---");
}

// put - places a node/inserts an item at the end of the deque
void put(Deque *deque, int value) {
    // create a new node, set its value, then set its next to NULL
    // if tail is not null, set its next to newnode
    // set tail to newnode
    // if head is null, set it to point to newnode

    return;
}

// dequeue - removes and returns the item at the head of the deque
int dequeue(Deque *deque) {
    // check if head is null
    // get value of head
    // set temp pointer to head
    // set head = head->next
    // free temp
    // if head is null, set tail to null also
    return 0;
}

// pop - removes an item from the tail of the queue
int pop(Deque *deque) {
    // get value of tail
    // create temp that points to tail
    // set tail to head
    // traverse till next node is temp
    // free temp
    // return popped value
    return 0;
}