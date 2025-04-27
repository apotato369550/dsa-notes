#include <stdio.h>
#include <limits.h>


// declare different constants
#define DEQUE_EMPTY INT_MIN
#define EMPTY INT_MAX
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
int dequeue(Deque *deque);

// pop - removes and returns the element at the tail of the array
int pop(Deque *deque);

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
                displayDeque(deque);
                break;
            case 2:
                printf("Putting an item into the deque... \n");
                int value = 0;
                printf("Please enter value to put: ");
                scanf("%d", &value);
                put(&deque, value);
                break;
            case 3:
                printf("Dequeueing an item from the deque... \n");
                int dequeued = dequeue(&deque);
                if (dequeued != DEQUE_EMPTY) {
                    printf("Dequeued value: %d\n", dequeued);
                }
                break;
            case 4:
                printf("Popping an item from the deque...\n");
                int popped = pop(&deque);
                if (popped != DEQUE_EMPTY) {
                    printf("Popped value: %d\n", popped);
                }
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
    // fix this
    // DEFINITELY fix this
    printf("---- START OF DEQUE ---\n");
    for (int i = 0; i < deque.count; i++) {
        int try = (deque.head + i) % MAX_DEQUE_SIZE;
        printf("Index [%d]: %d\n", i, deque.array[try]);
    }
    printf("---- END  OF DEQUE ---\n");
}

// push/enqueue/put function - adds element to the end of the array
void put(Deque *deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full! Failed to put/insert...\n");
        return;
    }
    deque->array[deque->tail] = value;
    deque->tail = (deque->tail + 1) % MAX_DEQUE_SIZE;
    printf("Value of tail: %d\n", deque->tail);
    deque->count += 1;
    printf("Successfully put value (%d) in deque.\n", value);
}

// dequeue - removes and returns the element at the front of the array
int dequeue(Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty! Failed to dequeue...\n");
        return DEQUE_EMPTY;
    }
    int dequeuedValue = deque->array[deque->head];
    deque->head = (deque->head + 1) % MAX_DEQUE_SIZE;
    deque->count -= 1;
    return dequeuedValue;
}

// pop - removes and returns the element at the tail of the array
int pop(Deque *deque) {
    // there's something wrong with pop
    if (isEmpty(deque)) {
        printf("Deque is empty! Failed to pop...\n");
        return DEQUE_EMPTY;
    }
    int popped = deque->array[deque->tail - 1];
    deque->tail = deque->tail - 1;
    if (deque->tail < 0) {
        deque->tail = MAX_DEQUE_SIZE - 1;
    }
    deque->count -= 1;
    return popped;
}

// isEmpty - checks if deque is empty
int isEmpty(Deque *deque) {
    return deque->count <= 0 ? 1 : 0;
}

// isfull - checks if deque is full
int isFull(Deque *deque) {
    return deque->count >= MAX_DEQUE_SIZE - 1 ? 1 : 0;
}