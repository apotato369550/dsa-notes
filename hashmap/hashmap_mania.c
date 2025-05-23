#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASHTABLE_LENGTH 10
#define MAX_NAME_LENGTH 50
#define DELETED_PERSON (Person *) 0xffffff

// fix errors for deleted person

typedef struct Person {
    char name[MAX_NAME_LENGTH];
    struct Person *next;
} Person, *PersonPointer;


int hash(char *string);
int initializeHashMap(PersonPointer *hashMap);
void displayHashmap(PersonPointer *hashMap);
int insertSeparateChaining(PersonPointer *hashMap, char *personName);
int insertOpenAddressing(PersonPointer *hashMap, char *personName);
int deletePerson(PersonPointer *hashMap, char *personName);
Person *findPerson(PersonPointer *hashMap, char *personName);
int populateHashmap(PersonPointer *hashMap);

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

int main() {
    PersonPointer hashMap[MAX_HASHTABLE_LENGTH];
    initializeHashMap(hashMap);
    int input = -1;
    char name[MAX_NAME_LENGTH];
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
        printf("7 - Populate hashmap\n");

        printf("Enter a choice: ");
        scanf("%d", &input);

        switch(input) {
            case 0:
                printf("Goodbye:)) See you next time!");
                break;
            case 1:
                printf("Displaying current hashmap...\n");
                displayHashmap(hashMap);
                break;
            case 2:
                printf("Inserting person to hashmap via separate chaining...\n");
                printf("Please enter name to insert: ");
                while(getchar() != '\n');
                gets(name);
                insertSeparateChaining(hashMap, name);
                break;
            case 3:
                printf("Inserting person to hashmap via open addressing...\n");
                printf("Please enter name to insert: ");
                while(getchar() != '\n');
                gets(name);
                insertOpenAddressing(hashMap, name);
                break;
            case 4:
                printf("Attempting to delete person from hashmap...\n");
                printf("Please enter name to delete: ");
                while(getchar() != '\n');
                gets(name);
                deletePerson(hashMap, name);
                break;
            case 5:
                printf("Checking if person exists in hashmap...\n");
                break;
            case 6:                
                printf("Checking hash value of person's name...\n");
                printf("Please enter name to hash: ");
                while(getchar() != '\n');
                gets(name);
                printf("Hash value of %s = %d", name, hash(name));
                break;
            case 7:
                printf("Populating hashmap...");
                populateHashmap(hashMap);
            default:
                printf("Please enter a valid input...\n");
                break;
        }
    }
    return 0;
}

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

int initializeHashMap(PersonPointer *hashMap) {
    for (int i = 0; i < MAX_HASHTABLE_LENGTH; i++) {
        hashMap[i] = NULL;
    }
    return 1;
}

void displayHashmap(PersonPointer *hashMap) {
    printf("--- START OF HASHMAP ---\n");
    for (int i = 0; i < MAX_HASHTABLE_LENGTH; i++) {
        printf("Index: %d = ", i);
        Person *currentPerson = hashMap[i];
        if (currentPerson == NULL) {
            printf(" Empty...");
        } else if(currentPerson == DELETED_PERSON) {
            printf("DELETED");
        } else {
            // use && instead of || to avoid infinite loop
            while (currentPerson != NULL && currentPerson != DELETED_PERSON) {
                printf("%s", currentPerson->name);
                if (currentPerson->next != NULL) {
                    printf(" -> ");
                }
                currentPerson = currentPerson->next;
            }
            if (currentPerson == DELETED_PERSON) {
                printf("DELETED");
            }
        }
        printf("\n");
    }
    printf("--- END OF HASHMAP ---\n");
    printf("Successfully displayed hashmap!\n");
}

int insertSeparateChaining(PersonPointer *hashMap, char *personName) {
    if (findPerson(hashMap, personName) != NULL) {
        printf("Person: %s already exists in hashmap!", personName);
        return 0;
    }
    int hashedIndex = hash(personName);
    Person *newPerson = malloc(sizeof(Person));
    strcpy(newPerson->name, personName);
    if (hashMap[hashedIndex] == NULL) {
        hashMap[hashedIndex] = newPerson;
    } else {
        Person *temp = hashMap[hashedIndex];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPerson;
    }
    printf("Successfully inserted person via externam chaining!\n");
    return 1;
}

int insertOpenAddressing(PersonPointer *hashMap, char *personName) {
    if (findPerson(hashMap, personName) != NULL) {
        printf("Person: %s already exists in hashmap!", personName);
        return 0;
    }
    int hashedIndex = hash(personName);
    for (int i = 0; i < MAX_HASHTABLE_LENGTH; i++) {
        int try = (hashedIndex + i) % MAX_HASHTABLE_LENGTH;
        if (hashMap[try] == NULL) {
            Person *newPerson = malloc(sizeof(Person));
            strcpy(newPerson->name, personName);
            newPerson->next = NULL;
            hashMap[try] = newPerson;
            printf("Successfully inserted person via open addressing!\n");
            return 1;
        }
    }
    printf("Hashmap is full! Failed to insert person via open addressing...\n");
    return 0;
}

int deletePerson(PersonPointer *hashMap, char *personName) {
    int hashedIndex = hash(personName);
    for (int i = 0; i < MAX_HASHTABLE_LENGTH; i++) {
        int try = (hashedIndex + i) % MAX_HASHTABLE_LENGTH;
        if (hashMap[try] == NULL) {
            printf("Person not found! Person might already be deleted! \n");
            return 0;
        }
        if (hashMap[try] == DELETED_PERSON) {
            continue;
        }
        if (strcmp(hashMap[try]->name, personName) == 0) {
            // delete it
            if (hashMap[try]->next == NULL || hashMap[try]->next == DELETED_PERSON) {
                printf("Attempting to delete person: %s\n", personName);
                // if it's the only person in the slot, just free it and set to NULL
                // delete it normally
                free(hashMap[try]);
                hashMap[try] = DELETED_PERSON;
                printf("Successfully deleted person: %s\n", personName);
                return 1;
            } else {
                printf("Attempting to delete person: %s\n", personName);
                // perform delete first
                Person *temp = hashMap[try];
                hashMap[try] = hashMap[try]->next;
                free(temp);
                printf("Successfully deleted person: %s\n", personName);
                return 1;
            }
        } else {
            // otherwise, traverse the linked list and delete if it's there
            Person *currentPerson = hashMap[try];
            // use && instead of || to avoid infinite loop -> source of "Ella Bug"
            while (currentPerson->next != NULL && currentPerson->next != DELETED_PERSON) {
                if (strcmp(currentPerson->next->name, personName) == 0) {
                    Person *temp = currentPerson->next;
                    currentPerson->next = temp->next;
                    free(temp);
                    printf("Successfully deleted person: %s\n", personName);
                    return 1;
                }
                currentPerson = currentPerson->next;
            }
        }
    }
    printf("Unable to find person %s. Deletion failed... \n", personName);
    return 0;
}

Person *findPerson(PersonPointer *hashMap, char *personName) {
    int hashedIndex = hash(personName);
    for (int i = 0; i < MAX_HASHTABLE_LENGTH; i++) {
        int try = (hashedIndex + i) % MAX_HASHTABLE_LENGTH;
        if (hashMap[try] == NULL) {
            return NULL;
        }
        if (hashMap[try] == DELETED_PERSON) {
            continue;
        }

        if (strcmp(hashMap[try]->name, personName) == 0) {
            // if person is found, return pointer to person
            return hashMap[try];
        } else {
            // otherwise, traverse linked list chain to find person
            Person *currentPerson = hashMap[try];
        }
    }
    return NULL;
}

int populateHashmap(PersonPointer *hashMap) {// Open Addressing
    insertOpenAddressing(hashMap, "John");
    insertOpenAddressing(hashMap, "Alice");
    insertOpenAddressing(hashMap, "Bob");
    insertOpenAddressing(hashMap, "Clara");
    insertOpenAddressing(hashMap, "David");
    insertOpenAddressing(hashMap, "Ella");
    insertOpenAddressing(hashMap, "Frank");
    
    insertSeparateChaining(hashMap, "Jordan");
    insertSeparateChaining(hashMap, "Grace");
    insertSeparateChaining(hashMap, "Hannah");
    insertSeparateChaining(hashMap, "Isaac");
    insertSeparateChaining(hashMap, "Jasmine");
    insertSeparateChaining(hashMap, "Kyle");
    insertSeparateChaining(hashMap, "Liam");
}