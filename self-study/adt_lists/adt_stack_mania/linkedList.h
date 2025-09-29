#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "studtype.h"

#define MAX 10

typedef struct Node {
    studtype data;
    struct Node *link;
} *Stack, Node;

void initList(Stack *S);
void push(Stack *S, studtype student);
void pop(Stack *S);
studtype top(Stack S);
bool isEmpty(Stack S);
bool isFull(Stack S);

#endif