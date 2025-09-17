#include "cursorBased.h"

void initVirtualHeap(Stack *L) {
    for (int i = 0; i < MAX; L->Elem[i].link = i - 1, i++) {}
    L->Avail = MAX - 1;
}

int allocSpace(Stack *L) {
    int newPointer = L->Avail;
    if (newPointer != -1) {
        L->Avail = L->Elem[newPointer].link;
    }
    return newPointer;
}

void deallocSpace(Stack *L, int pointer) {
    L->Elem[pointer].link = L->Avail;
    L->Avail = pointer;
}

void initList(Stack *S) {
    S->Stack = -1;
}

void push(Stack *S, studtype student) {
    if (isFull(*S) != true) {
        int newNode = allocSpace(S);
        if (newNode != -1) {
            S->Elem[newNode].data = student;
            S->Elem[newNode].link = S->Stack;
            S->Stack = newNode;
        }
    }
}

void pop(Stack *S) {
    if (isEmpty(*S) != true) {
        int temp = S->Stack;
        S->Stack = S->Elem[temp].link;
        deallocSpace(S, temp);
    }
}

studtype top(Stack S) {
    if (isEmpty(S) != true) {
        return S.Elem[S.Stack].data;
    } else {
        // bug: missing default return statement lol
        // fix: add a dummy and return it
        studtype dummy = {{"XXXXX", "XXXXX", 'X'}, -1, "XXXXX", "XXXXX"};
        return dummy;
    }
}

bool isEmpty(Stack S) {
    return S.Stack == -1;
}

bool isFull(Stack S) {
    return S.Avail == -1;
}

