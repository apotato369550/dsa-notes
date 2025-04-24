#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

void initializeQueue(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);

int main() {
    Queue queue;

    initializeQueue(&queue);

    for(int i = 0; i < 5; i++) {
        enqueue(&queue, i + 1);
        printf("Successfully enqueued value: %d\n", i + 1);
    }

    for (int i = 0; i < 6; i++) {
        int dequeued = dequeue(&queue);
        if (dequeued == QUEUE_EMPTY) {
            printf("Queue is empty! Nothing to dequeue\n");
        } else {
            printf("Dequeued value: %d\n", dequeued);
        }
    }

    return 0;
}

void initializeQueue(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

void enqueue(Queue *queue, int value) {
    // create new node and set its next to null
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    // if tail is not null (node already exists), set its next to newnode
    if (queue->tail != NULL) {
        queue->tail->next = newNode;
    }
    // set tail equal to newnode
    queue->tail = newNode;

    // if head is null, set it to point to the new node
    if (queue->head == NULL) {
        queue->head = newNode;
    }
    return;
}

int dequeue(Queue *queue) {
    // check if head is null (queue is empty). if empty, just return
    if (queue->head == NULL) {
        return QUEUE_EMPTY;
    }

    // create a temp pointer equal to head
    Node *temp = queue->head;
    // create a variable to store the dequeued value and set it to temp's value
    int deqeued = temp->value;
    // set head equal to its next
    queue->head = queue->head->next;
    // free temp

    free(temp);
    // if head is null, set tail to null also
    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    return deqeued;
}
