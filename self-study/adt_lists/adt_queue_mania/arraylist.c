#include "arraylist.h"

// remember the conditions for circular queue:
// if empty: front ahead by rear by 1
// if full: front ahead by rear by 2
// if 1 element: front = rear

// front should be 
void initQueue(Queue *Q) {
    // bug: rear should be 0 and front should be 1
    // since front should be ahead by rear by 1 if empty
    Q->rear = 0;
    Q->front = 1;
}

// increment first, then insert the element
void enqueue(Queue *Q, studtype student) {
    if (isFull(*Q) != true) {
        Q->rear = (Q->rear + 1) % MAX;
        Q->Elem[Q->rear] = student;
    }
}

void dequeue(Queue *Q) {
    if (isEmpty(*Q) != true) {
        Q->front = (Q->front + 1) % MAX;
    }
}

studtype front(Queue Q) {
    if (isEmpty(Q) != true) {
        return Q.Elem[Q.front];
    } else {
        // bug: missing default return statement lol
        // fix: add a dummy and return it
        studtype dummy = {{"XXXXX", "XXXXX", 'X'}, -1, "XXXXX", "XXXXX"};
        return dummy;
    }
}

bool isEmpty(Queue Q) {
    return (Q.rear + 1) % MAX == Q.front;
}
bool isFull(Queue Q) {
    return (Q.rear + 2) % MAX == Q.front;
}