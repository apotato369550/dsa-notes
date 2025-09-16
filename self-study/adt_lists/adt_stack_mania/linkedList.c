#include "linkedList.h"

void initList(Stack *S) {
    S = NULL;
}

void push(Stack *S, studtype student) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = student;
        newNode->link = *S;
        *S = newNode;
    }
}

void pop(Stack *S) {
    if (isEmpty(*S) != true) {
        Node *temp = *S;
        *S = temp->link;
        free(temp);
    }
}

studtype top(Stack S) {
    return S->data;
}

bool isEmpty(Stack S) {
    return S == NULL;
}

bool isFull(Stack S) {
    return false;
}