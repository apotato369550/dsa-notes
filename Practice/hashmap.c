#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHMAP_MAX_LENGTH 10
#define MAX_NAME_LENGTH 50

// steps of creating a hash table
// 1. create a struct for the data to be stored in the hash table
// 2. create a hash function to convert the data into an index
// 3. create a table to store the data (in the form of an array of structs)
// 4. create a function to insert data into the hash table

typedef struct Person {
    char name[MAX_NAME_LENGTH];
    int age;
    struct Person *next;
} Person;


int hash(char *name) {
    int length = strlen(name);
    int hash = 0;

    for (int i = 0; i < length; i++) {
        hash += (int) name[i];
        hash *= (int) name[i];
        hash %= HASHMAP_MAX_LENGTH;
    }

    return hash;
}

int insertToHashTable(Person *hashTable, Person person) {
    printf("Inserting to hash table!");
    int index = hash(person.name);
    
    // something is wrong here
    if (hashTable[index].age != -1) {
        // insert new person at index and stuff
        Person *current = &(hashTable[index]);
        while (current->next == NULL) {
            current = current->next;
        }
        Person *newPerson = malloc(sizeof(Person));
        newPerson->next = NULL;
        strcpy(newPerson->name, person.name);
        newPerson->age = person.age;
        current->next = newPerson;
    } else {
        strcpy(hashTable[index].name, person.name);
        hashTable[index].age = person.age;
    }


    return 1;
}

void initializeHashTable(Person *hashTable) {
    for (int i = 0; i < HASHMAP_MAX_LENGTH; i++) {
        hashTable[i].age = -1;
        strcpy(hashTable[i].name, "");
        hashTable[i].next = NULL;
    }
}

void printHashTable(Person *hashTable) {
    printf("Printing Hash Table: \n");
    for (int i = 0; i < HASHMAP_MAX_LENGTH; i++) {
        Person *current = &(hashTable[i]);
        while (current != NULL) {
            printf("Name: %s \t---\t Age: %d \n", current->name, current->age);
            current = current->next;
        }
    }
}

int main() {
    Person personHashTable[HASHMAP_MAX_LENGTH];

    initializeHashTable(personHashTable);

    Person jake = {"Jake", 25};
    Person john = {"John", 30};
    Person jeremy = {"Jeremy", 35};
    Person jessica = {"Jessica", 28};
    Person jill = {"Jill", 22};

    printf("Hash Value for %s: %d\n", jake.name, hash(jake.name));
    printf("Hash Value for %s: %d\n", john.name, hash(john.name));
    printf("Hash Value for %s: %d\n", jeremy.name, hash(jeremy.name));
    printf("Hash Value for %s: %d\n", jessica.name, hash(jessica.name));
    printf("Hash Value for %s: %d\n", jill.name, hash(jill.name));

    insertToHashTable(personHashTable, jake);
    insertToHashTable(personHashTable, john);
    insertToHashTable(personHashTable, jeremy);
    insertToHashTable(personHashTable, jessica);
    insertToHashTable(personHashTable, jill);
    
    printHashTable(personHashTable);
    return 0;
}