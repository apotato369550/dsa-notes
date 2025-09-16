#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "studtype.h"

#define MAX 10

typedef struct Node {
    studtype data;
    struct Node *link;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} *Queue;

void initQueue(Queue *Q);
void enqueue(Queue *Q, studtype student);
void dequeue(Queue *Q);
studtype front(Queue Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);

#endif