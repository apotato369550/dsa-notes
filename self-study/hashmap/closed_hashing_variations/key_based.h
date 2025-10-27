#ifndef KEY_BASED
#define KEY_BASED

#include <stdbool.h>

#define MAX 11
#define EMPTY '*'
#define DELETED '?'

typedef struct {
    char data;
    int link;
} Cell;

typedef struct {
    Cell Elem[MAX * 2];
    // initialize avail to first cell in separate thingy
    int avail;
} Dictionary;

void initializeDictionary(Dictionary *D);

// cursor-based helper functions
int allocSpace(Dictionary *D);
void deallocSpace(Dictionary *D, int pointer);

// maybe add more? this looks very interesting lol

int hash(char elem);
void insert(Dictionary *D, char elem);
void deleteElem(Dictionary *D, char elem);
bool search(Dictionary D, char elem);
int getIndex(Dictionary D, char elem);
void printDictionary(Dictionary D);

#endif