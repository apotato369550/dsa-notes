#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "studtype.h"

#define MAX 10
typedef struct {
    studtype Elem[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue *Q);
void enqueue(Queue *Q, studtype student);
void dequeue(Queue *Q);
studtype front(Queue Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);

// enqueue
// dequeue
// front
// isempty
// isfull

#endif