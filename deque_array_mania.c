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

// selection menu - user selects - done

// function prototypes: 
// initialize - sets head and tail to default position
void initializeDeque(Deque *deque);

// display - display the elements of the deqeue
void displayDeque(Deque deque);

// push/enqueue/put function - adds element to the end of the array
void put(Deque *deque, int value);

// deqeue - removes and returns the element at the front of the array
void dequeue(Deque *deque);

// pop - removes and returns the element at the tail of the array
void pop(Deque *deque);

// isEmpty - checks if deque is empty
int isEmpty(Deque *deque);

// isfull - checks if deque is full
int isFull(Deque *deque);


// things to look out for:
// wrap-around cases for queues - queues sometimes wrap around. i don't know how this will affect how popping works

int main() {
    int input = -1;
    Deque deque;
    initializeDeque(&deque);
    printf("Welcome to deque array mania! Where values are popped fresh from the vine!\n");
    while (input != 0) {
        printf("Please select from the following choices to proceed: \n");
        printf("0 - Exit\n");
        printf("1 - Display all items in deque\n");
        printf("2 - Put an item into the deque\n");
        printf("3 - Dequeue/remove an item from the head of the deque\n");
        printf("4 - Pop/remove an item from the tail of the deque \n");
        printf("Please select an option: ");
        scanf("%d", &input);

        switch(input) {
            case 0:
                printf("See you next time! :)) \n");
                break;
            case 1:
                printf("Displaying all items in deque...\n");
                break;
            case 2:
                printf("Putting an item into the deque... \n");
                break;
            case 3:
                printf("Dequeueing an item from the deque... \n");
                break;
            case 4:
                printf("Popping an item from the deque...\n");
                break;
            default:
                printf("Please enter a valid option...\n");
        }
    }
    return 0;
}


// function prototypes: 
// initialize - sets head and tail to default position
void initializeDeque(Deque *deque) {
    deque->head = 0;
    deque->tail = 0;
    deque->count = 0;
}

// display - display the elements of the deqeue
void displayDeque(Deque deque) {
    for (int i = 0; i < deque.count; i++) {
        printf("Index [%d]: %d\n", i, deque.array[i]);
    }
}

// push/enqueue/put function - adds element to the end of the array
void put(Deque *deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full! Failed to put/insert...\n");
        return;
    }
    deque->array[deque->tail] = value;
    deque->tail += (deque->tail + 1) % MAX_DEQUE_SIZE;
    deque->count += 1;
}

// deqeue - removes and returns the element at the front of the array
void dequeue(Deque *deque);

// pop - removes and returns the element at the tail of the array
void pop(Deque *deque);

// isEmpty - checks if deque is empty
int isEmpty(Deque *deque);

// isfull - checks if deque is full
int isFull(Deque *deque);