#include <stdio.h>
#include <limits.h>

#define QUEUE_LENGTH 5
#define QUEUE_EMPTY INT_MIN

typedef struct Queue {
    int top;
    int bottom;
    int array[QUEUE_LENGTH];
} Queue;

// implement circular queue

void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);

int main() {
    Queue queue;
    queue.top = 0;
    queue.bottom = -1;

    enqueue(&queue, 3);
    enqueue(&queue, 4);
    enqueue(&queue, 5);

    for (int i = 0; i < QUEUE_LENGTH; i++) {
        dequeue(&queue);
    }

    return 0;
}

void enqueue(Queue *queue, int value) {
    if (queue->bottom < QUEUE_LENGTH) {
        queue->bottom += 1;
        queue->array[queue->bottom] = value;
        printf("Sucessfully enqueued the value: %d\n", value);
    } else {    
        printf("The queue is full! Failed to enqueue!\n");
    }
}

int dequeue(Queue *queue) {
    if (queue->top > queue->bottom) {
        printf("Queue is empty! Failed to dequeue!");
        queue->top = 0;
        queue->bottom = -1;
        return QUEUE_EMPTY;
    }
    int dequeued = queue->array[queue->top];
    queue->top++;

    return dequeued;
}