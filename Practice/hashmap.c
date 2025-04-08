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
    // struct Person *next;
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
    int index = hash(person.name);

    if (hashTable[index].age != -1) {
        return 0;
    }

    strcpy(hashTable[index].name, person.name);
    hashTable[index].age = person.age;

    return 1;
}

void initializeHashTable(Person *hashTable) {
    for (int i = 0; i < HASHMAP_MAX_LENGTH; i++) {
        hashTable[i].age = -1;
        strcpy(hashTable[i].name, "");
    }
}

void printHashTable(Person *hashTable) {
    printf("Printing Hash Table: \n");
    for (int i = 0; i < HASHMAP_MAX_LENGTH; i++) {
        printf("Name: %s \t---\t Age: %d \n", hashTable[i].name, hashTable[i].age);
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

    printf("Hello World!");
    return 0;
}