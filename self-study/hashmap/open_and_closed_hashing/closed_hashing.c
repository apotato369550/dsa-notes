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
void deleteElem(Dictionary D, char elem) {
    int i, traverseCount;
    if (!search(D, elem)) return;
    for (i = hash(elem), traverseCount = 0; traverseCount < MAX && D[i] != EMPTY && D[i] != elem; i = (i + 1) % MAX, traverseCount++) {}
    if (traverseCount != MAX) D[i] = DELETED;
}

bool search(Dictionary D, char elem) {
    int i, searchCount;
    bool foundFlag = false;
    for (i = hash(elem), searchCount = 0; searchCount < MAX && D[i] != EMPTY && foundFlag == false; i = (i + 1) % MAX, searchCount++) {
        if (D[i] == elem) foundFlag = true;
    }
    return foundFlag;
}

int getIndex(Dictionary D, char elem) {
    int i, searchCount;
    bool foundFlag = false;
    for (i = hash(elem), searchCount = 0; searchCount < MAX && D[i] != EMPTY && foundFlag == false; i = (i + 1) % MAX, searchCount++) {
        if (D[i] == elem) foundFlag = true;
    }
    return i;

}

void printDictionary(Dictionary D) {
    printf("\n---PRINTING DICTIONARY---\n");
    for (int i = 0; i < MAX; i++) {
        printf("[%d] = %c\n", i, D[i]);
    }
    printf("\n---DICTIONARY END---\n");
}