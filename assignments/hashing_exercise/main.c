#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 10
#define EMPTY '*'
#define DELETED '?'

typedef char Dictionary[MAX];

void initializeDictionary(Dictionary D);
int hash(char elem);
void insert(Dictionary D, char elem);
void delete(Dictionary D, char elem);
int getSearchLength(Dictionary D, char elem);
void printDictionary(Dictionary D);

int main() {
    char elements[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int elementCount = 8;
    Dictionary D;
    initializeDictionary(D);
    for (int i = 0; i < elementCount; i++) {
        insert(D, elements[i]);
    }
    printDictionary(D);
    int searchLengthSum = 0;
    for (int i = 0; i < elementCount; i++) {
        int searchLength = getSearchLength(D, elements[i]);
        searchLengthSum += searchLength;
        printf("Search length of %c: %d\n", elements[i], searchLength);
    }
    printf("Total search length: %d\n", searchLengthSum);

    float meanSearchLength = (float) searchLengthSum / (float) elementCount;
    printf("Mean search length: %.2f\n", meanSearchLength);

    return 0;
}

void initializeDictionary(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        D[i] = EMPTY;
    }
}

int hash(char elem) {
    if (elem == 'A') {
        return 1;
    } else if (elem == 'B' || elem == 'G') {
        return 4;
    } else if (elem == 'C' || elem == 'D') {
        return 9;
    } else if (elem == 'E') {
        return 0;
    } else if (elem == 'F' || elem == 'H') {
        return 3;
    } 
    return elem % MAX;
}

bool search(Dictionary D, char elem) {
    int i, searchCount;
    bool foundFlag = false;
    for (i = hash(elem), searchCount = 0; searchCount < MAX && D[i] != EMPTY && foundFlag == false; i = (i + 1) % MAX, searchCount++) {
        if (D[i] == elem) foundFlag = true;
    }
    return foundFlag;
}

void insert(Dictionary D, char elem) {
    int insertionCount;
    int i;
    // if the element exists and the list isn't full, we insert
    if (search(D, elem)) return;
    for (i = hash(elem), insertionCount = 0; insertionCount < MAX && D[i] != EMPTY && D[i] != DELETED; i = (i + 1) % MAX, insertionCount++) {}
    if (insertionCount != MAX) D[i] = elem;
}

void delete(Dictionary D, char elem) {
    // the logic is kinda iffy
    // should find if it exists first, then delete
    // i don't think it can be done both at once
    // gotta modify it for sure
    int i;
    int traverseCount;
    if (!search(D, elem)) return;
    for (i = hash(elem), traverseCount = 0; traverseCount < MAX && D[i] != EMPTY && D[i] != elem; i = (i + 1) % MAX, traverseCount++) {}
    if (traverseCount != MAX) D[i] = DELETED;
}

int getSearchLength(Dictionary D, char elem) {
    int i;
    int searchCount;
    if (!search(D, elem)) {
        // printf("Element cannot be found \n");
        return 0;
    }
    for (i = hash(elem), searchCount = 0; D[i] != elem; i = (i + 1) % MAX, searchCount++) {}
    return searchCount + 1;
}

void printDictionary(Dictionary D) {
    printf("\n---PRINTING DICTIONARY---\n");
    for (int i = 0; i < MAX; i++) {
        printf("[%d] = %c\n", i, D[i]);
    }
    printf("\n---DICTIONARY END---\n");
}