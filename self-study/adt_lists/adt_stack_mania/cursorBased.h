#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "studtype.h"

#define MAX 10

typedef struct {
    studtype data;
    int link;
} nodetype;

typedef struct {
    nodetype Elem[MAX];
    int Avail;
    int Stack;
} Stack;

void initList(Stack S);
void push(Stack S, studtype student);
void pop(Stack S);
studtype top(Stack S);
bool isEmpty(Stack S);
bool isFull(Stack S);

#endif