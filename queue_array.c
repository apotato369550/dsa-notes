#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN

typedef struct Queue {
    int head;
    int tail;
    int count;
    int size;
    int *array;
} Queue;

// implement circular queue

void initializeQueue(Queue *queue, int size);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
int isQueueEmpty(Queue *queue);
int isQueueFull(Queue *queue);

int main() {
    Queue queue;

    enqueue(&queue, 3);
    enqueue(&queue, 4);
    enqueue(&queue, 5);

    for (int i = 0; i < 5; i++) {
        dequeue(&queue);
    }

    return 0;
}

void initialize_queue(Queue *queue, int size) {
    queue->head = 0;
    queue->tail = size - 1;
    queue->count = 0;
    queue->size = size;
    queue->array = malloc(sizeof(int) * size);
}

void enqueue(Queue *queue, int value) {
    if (isQueueFull(queue)) {
        printf("Queue is full! Failed to enqueue.\n");
        return;
    }
    queue->array[queue->tail] = value;
    queue->count += 1;
    queue->tail = (queue->tail + 1) % queue->size;
    printf("Successfully enqueued: %d\n", value);
    return;
}

int dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty! Failed to dequeue.\n");
        return QUEUE_EMPTY;
    }
    int dequeued = queue->array[queue->head];
    queue->head = (queue->head + 1) % queue->size;
    queue->count -= 1;
    return dequeued;
}

int isQueueEmpty(Queue *queue) {
    if (queue->count == 0) {
        return 1;
    }
    return 0;
}

int isQueueFull(Queue *queue) {
    if (queue->count == queue->size) {
        return 1;
    }
    return 0;
}
