#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STACK_EMPTY INT_MIN

typedef struct Node {
    int value;
    struct Node *next;
} Node, *Stack;

void push(Stack *stack, int value);
int pop(Stack *stack);
void printStack(Stack stack);

int main() {
    Stack stack = NULL;

    push(&stack, 3);
    push(&stack, 4);
    push(&stack, 5);
    push(&stack, 6);

    printStack(stack);

    for (int i = 0; i < 5; i++) {
        int popped = pop(&stack);
        if (popped != STACK_EMPTY) {
            printf("Popped: %d\n", popped);
        } else {
            printf("Stack empty! Nothing to pop!\n");
        }
    }

    return 0;
}


void push(Stack *stack, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    
    if (*stack == NULL) {
        *stack = newNode;
    } else {
        // this is wrong
        newNode->next = *stack;
        (*stack) = newNode;
    }
    printf("Successfully pushed new node: %d\n", value);
    return;
}


int pop(Stack *stack) {
    if (*stack == NULL) {
        return STACK_EMPTY;
    }
    int popped = (*stack)->value;
    Node *temp = *stack;
    (*stack) = (*stack)->next;
    free(temp);

    return popped;
}

void printStack(Stack stack) {
    while (stack != NULL) {
        printf("Stack value: %d\n", stack->value);
        stack = stack->next;
    }
    return;
}