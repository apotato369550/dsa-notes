#include "cursorBased.h"

void initVirtualHeap(Queue *L) {
    for (int i = 0; i < MAX; L->Elem[i].link = i - 1, i++) {}
    L->Avail = MAX - 1;
}

int allocSpace(Queue *L) {
    int newPointer = L->Avail;
    if (newPointer != -1) {
        L->Avail = L->Elem[newPointer].link;
    }
    return newPointer;
}

void deallocSpace(Queue *L, int pointer) {
    L->Elem[pointer].link = L->Avail;
    L->Avail = pointer;
}

void initQueue(Queue *Q) {
    Q->front = -1;
    Q->rear = -1;
}

void enqueue(Queue *Q, studtype student) {
    // enqueue when empty
    // enqueue when one item
    // enqueue when multiple item :VVV
    int newNode = allocSpace(Q);
    if (newNode != NULL) {
        Q->Elem[newNode].data = student;
        Q->Elem[newNode].link = NULL;
        // must check if empty :VV
        if (Q->rear == -1) {
            Q->rear = newNode;
            Q->front = newNode;
        } else {
            Q->Elem[Q->rear].link = newNode;
            Q->rear = newNode;
        }
    }
}

void dequeue(Queue *Q) {
    if (empty(*Q) != true) {
        int temp = Q->front;
        Q->front = Q->Elem[temp].link;
        deallocSpace(Q, temp);
        if (Q->front == -1) {
            Q->rear = -1;
        }
    }
}

studtype front(Queue Q) {
    return Q.Elem[Q.front].data;
}

bool isEmpty(Queue Q) {
    return Q.front == -1 && Q.rear == -1;
}

bool isFull(Queue Q) {
    return Q.Avail == -1;
}