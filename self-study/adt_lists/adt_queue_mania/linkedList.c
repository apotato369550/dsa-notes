#include "linkedList.h"

void initQueue(Queue *Q) {
    (*Q)->front = NULL;
    (*Q)->rear = NULL;
}

void enqueue(Queue *Q, studtype student) {
    // enqueue when empty
    // enqueue when one item
    // enqueue when multiple item :VVV
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = student;
        newNode->link = NULL;
        // must check if empty :VV
        if ((*Q)->rear == NULL) {
            (*Q)->rear = newNode;
            (*Q)->front = newNode;
        } else {
            (*Q)->rear->link = newNode;
            (*Q)->rear = newNode;
        }
    }
}

void dequeue(Queue *Q) {
    if (empty(*Q) != true) {
        Node *temp = (*Q)->front;
        (*Q)->front = temp->link;
        free(temp);
        if ((*Q)->front == NULL) {
            (*Q)->rear = NULL;
        }
    }
}

studtype front(Queue Q) {
    return Q->front->data;
}

bool isEmpty(Queue Q) {
    return Q->front == NULL && Q->rear == NULL;
}

bool isFull(Queue Q) {
    return false;
}