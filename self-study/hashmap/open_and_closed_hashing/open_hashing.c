#include "open_hashing.h"

void initializeDictionary(Dictionary D) {
    for (int i = 0; i < MAX_ENTRIES; i++) {
        D[i] = NULL;
    }
}

int hash(char elem) {
    // implement cool hashing function bro
    return elem % MAX_ENTRIES;
}

void insert(Dictionary D, char elem) {
    int hashed_index = hash(elem);
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = elem;
    newNode->link = NULL;
    // perform insert first basically
    if (D[hashed_index] == NULL) {
        D[hashed_index] = newNode;
    } else {
        newNode->link = D[hashed_index];
        D[hashed_index] = newNode;
    }
}

void deleteElem(Dictionary D, char elem);
bool search(Dictionary D, char elem);
int getIndex(Dictionary D, char elem);
int getSearchLength(Dictionary D, char elem);
void printDictionary(Dictionary D);
