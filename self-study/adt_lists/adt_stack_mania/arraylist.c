#include "arraylist.h"

void initList(Stack *S) {
    S->top = -1;
}

// omg. bug: isempty instead of isfull LMAOOO
// fix: change it to isfull
void push(Stack *S, studtype student) {
    if (isFull(*S) != true) {
        S->Elem[++(S->top)] = student;
    }
}

void pop(Stack *S) {
    if (isEmpty(*S) != true) {
        S->top--;
    }
}

// bug: same here. isempty instead of isfull
// fix: change it to isfull
studtype top(Stack S) {
    if (isFull(S) != true) {
        return S.Elem[S.top];
    } else {
        studtype dummy = {{"XXXXX", "XXXXX", 'X'}, -1, "XXXXX", "XXXXX"};
        return dummy;
    }
}

bool isEmpty(Stack S) {
    return S.top == -1;
}

bool isFull(Stack S) {
    return S.top + 1 == MAX;
}