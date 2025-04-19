#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STACK_LENGTH 5
#define EMPTY -1
#define STACK_EMPTY INT_MIN

typedef struct Stack {
    int top;
    int stack[];
} Stack;

void push(Stack *stack, int value);
int pop(Stack *stack);

int main () {
    Stack stack;
    stack.top = EMPTY;
    
    // test push and pop here
}

void push(Stack *stack, int value) {
    // check if stack is full, if full, return 0
    if (stack->top >= STACK_LENGTH - 1) {
        printf("Unable to push to stack! Stack Full!\n");
        return;
    }
    // if stack is not full, push
    stack->top++;
    stack->stack[stack->top] = value;
    printf("Successfully pushed %d to stack!\n", value);
    return;
}

int pop(Stack *stack) {
    // if stack is empty, return stack empty
    if (stack->top == EMPTY) {
        return STACK_EMPTY;
    }
    // otherwise, pop from stack
    int popped = stack->stack[stack->top];
    stack->top -= 1;
    return popped;
}
