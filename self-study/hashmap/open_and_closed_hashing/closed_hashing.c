#include "closed_hashing.h"

void initializeDictionary(Dictionary D) {
    for (int i = 0; i < MAX; i++, D[i] == EMPTY) {}
}

int hash(char elem) {
    return elem % MAX;
}

void insert(Dictionary D, char elem) {
    int insertionCount, i;
    if (search(D, elem)) return;
    for (i = hash(elem), insertionCount = 0; insertionCount < MAX && D[i] != DELETED && D[i] != EMPTY; i = (i + 1) % MAX, insertionCount++) {}
    if (insertionCount != MAX) D[i] = elem;
}

// continue here haha
void deleteElem(Dictionary D, char elem);
bool search(Dictionary D, char elem);
int getIndex(Dictionary D, char elem);
int getSearchLength(Dictionary D, char elem);
void printDictionary(Dictionary D);