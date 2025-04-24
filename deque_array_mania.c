#include <stdio.h>
#include <limits.h>


// declare different constants
#define DEQUE_EMPTY INT_MIN
#define DEQUE_FULL INT_MAX
#define MAX_DEQUE_SIZE 10

// array implementation of a deque
// todo:
// dequeue struct - stores head, tail, count, and array to contain contents of deque

typedef struct Deque {
    int head;
    int tail;
    int count;
    int array[MAX_DEQUE_SIZE];
} Deque;

// selection menu - user selects
// initialize - sets head and tail to default position
// display - display the elements of the deqeue
// push/enqueue/put function - adds element to the end of the array
// deqeue - removes and returns the element at the front of the array
// pop - removes and returns the element at the tail of the array
// isEmpty - checks if deque is empty
// isfull - checks if deque is full


// things to look out for:
// wrap-around cases for queues - queues sometimes wrap around. i don't know how this will affect how popping works

int main() {
    return 0;
}