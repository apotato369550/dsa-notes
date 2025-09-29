#include "linkedList.h"

void initList(Stack *S) {
    // bug: S, not *S
    // fix: S to *S
    *S = NULL;
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
    // bug: returns null if empty:( must return a dummy variable
    if (isEmpty(S) == true) {
        return S->data;
    } else {
        // bug: missing default return statement lol
        // fix: add a dummy and return it
        studtype dummy = {{"XXXXX", "XXXXX", 'X'}, -1, "XXXXX", "XXXXX"};
        return dummy;
    }
}

bool isEmpty(Stack S) {
    return S == NULL;
}

bool isFull(Stack S) {
    return false;
}