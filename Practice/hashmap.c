#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHMAP_MAX_LENGTH 10
#define MAX_NAME_LENGTH 50

typedef struct Person {
    char name[MAX_NAME_LENGTH];
    int age;
    struct Person *next;
} Person;

int hash(Person person) {
    char *name = person.name;
    int length = strlen(name);
    int hash = 0;

    for (int i = 0; i < length; i++) {

    }

    return hash;
}

int main() {
    printf("Hello World!");
    return 0;
}