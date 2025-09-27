#include <stdio.h>
#include <limits.h>

#define MAX 10
#define EMPTY -1
#define DELETED INT_MIN

typedef char Dictionary[MAX];

void initializeDictionary(Dictionary D);
int hash(char elem);
void insert(Dictionary D, char elem);
void delete(Dictionary D, char elem);


int main() {

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

void insert(Dictionary D, char elem) {
    int insertionCount;
    int i;
    // if the element exists and the list isn't full, we insert
    for (i = 0, insertionCount = 0; insertionCount < MAX && D[i] != EMPTY && D[i] != DELETED && D[i] != elem; i = (i + 1) % MAX, insertionCount++) {}
    if (insertionCount != MAX) D[i] = elem;
}

void delete(Dictionary D, char elem) {
    // the logic is kinda iffy
    // should find if it exists first, then delete
    // i don't think it can be done both at once
    // gotta modify it for sure
    int i;
    int traverseCount;
    for (i = 0, traverseCount = 0; traverseCount < MAX && D[i] != EMPTY && D[i] != elem; i = (i + 1) % MAX, traverseCount++) {}
    if (traverseCount != MAX) D[i] = DELETED;
}