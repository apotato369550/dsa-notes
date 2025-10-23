#ifndef OPEN_HASHING
#define OPEN_HASHING

#include <stdio.h>
#include <stdbool.h>

// fix: forgot to include stdlib.h
#include <stdlib.h>

#define MAX_ENTRIES 11

typedef struct Node{
    char data;
    struct Node *link;
} Node, *NodePointer;

typedef NodePointer Dictionary[MAX_ENTRIES];

void initializeDictionary(Dictionary D);
int hash(char elem);
void insert(Dictionary D, char elem);
void deleteElem(Dictionary D, char elem);
bool search(Dictionary D, char elem);
int getIndex(Dictionary D, char elem);
int getSearchLength(Dictionary D, char elem);
void printDictionary(Dictionary D);

#endif