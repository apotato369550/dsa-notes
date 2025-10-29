#include "double_hashing.h"

void initializeDictionary(Dictionary D) {
    // fix: change '==' into '='
    for (int i = 0; i < MAX; i++, D[i] = EMPTY) {}
}

int hash_1(char elem) {
    return elem * 7;
}

int hash_2(char elem) {
    return elem * 2;
}

int hash(char elem) {
    return (hash_1(elem) + hash_2(elem)) % MAX;
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
    for (i = hash(elem), searchCount = 0; searchCount < MAX && D[i] != EMPTY; i = (i + 1) % MAX, searchCount++) {
        if (D[i] == elem) return true;
    }
    return false;
}

int getIndex(Dictionary D, char elem) {
    int i, searchCount;
    // hmmmm
    // no need for foundflag. return i right away as it is found
    // dumb me lol
    // fix: removed redundant 'foundFlag' bool variable
    // fix: removed redundant '== false'
    for (i = hash(elem), searchCount = 0; searchCount < MAX && D[i] != EMPTY; i = (i + 1) % MAX, searchCount++) {
        // fix: instead of relying on a flag, return 'i' right away after it's found
        if (D[i] == elem) return i;
    }
    return -1;

}

void printDictionary(Dictionary D) {
    printf("\n---PRINTING DICTIONARY---\n");
    for (int i = 0; i < MAX; i++) {
        printf("[%d] = %c\n", i, D[i]);
    }
    printf("\n---DICTIONARY END---\n");
}