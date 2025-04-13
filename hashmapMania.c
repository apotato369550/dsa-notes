#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASHTABLE_LENGTH 10
#define MAX_NAME_LENGTH 50
#define DELETED_PERSON (uintptr_t) (0xfffffffffffffffful)

typedef struct Person {
    char name[MAX_NAME_LENGTH];
    struct Person *next;
} Person, *PersonPointer;

/*
todos: 
1. menu in main function
2. display function
3. separate chaining insert function
4. open addressing insert function
5. search function
6. delete function
7. hash function - done
8. view hash of string

notes:
make Person and PersonPointer struct - done
set the hashmap to an array of personpointers with length max_hashtable length
handle deleted persons properly
wrap-around for loop ints and stuff
*/ 

int hash(char *string) {
    int hash = 0;
    for (int i = 0; i < strlen(string); i++) {
        hash += i;
        hash += string[i];
        hash *= string[i];
        hash %= MAX_HASHTABLE_LENGTH;
    }
    return hash;
}

int main() {
    PersonPointer hashmap[MAX_HASHTABLE_LENGTH];
    int input = -1;
    printf("--- WELCOME TO HASHMAP MANIA ---");
    while (input != 0) {
        printf("Welcome to hash map mania! Entries are cooked daily! Here are your options: \n");
        printf("0 - Exit\n");
        printf("1 - Display the current hashmap\n");
        printf("2 - Insert person to hashmap (separate chaining) \n");
        printf("3 - Insert person to hashmap (open addressing) \n");
        printf("4 - Delete person from hashmap\n");
        printf("5 - Check if person exists in hashmap\n");
        printf("6 - View hash value of person's name\n");

        printf("Enter a choice: ");
        scanf("%d", &input);

        switch(input) {
            case 0:
                printf("Goodbye:)) See you next time!");
                break;
            case 1:
                printf("Displaying current hashmap...\n");
                break;
            case 2:
                printf("Inserting person to hashmap via separate chaining...\n");
                break;
            case 3:
                printf("Inserting person to hashmap via open addressing...\n");
                break;
            case 4:
                printf("Attempting to delete person from hashmap...\n");
                break;
            case 5:
                printf("Checking if person exists in hashmap...\n");
                break;
            case 6:                
                printf("Checking hash value of person's name...\n");
                break;

        }
    }
    return 0;
}