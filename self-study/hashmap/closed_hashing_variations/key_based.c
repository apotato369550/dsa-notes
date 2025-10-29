#include "key_based.h"

void initializeDictionary(Dictionary *D) {
    for (int i = 0; i < MAX; D->Elem[i].data = EMPTY, D->Elem[i].link = -1, i++) {}
    for (int i = MAX; i < MAX * 2; D->Elem[i].link = MAX - i - 1, i++) {}
    D->avail = (MAX * 2) - 1;
    D->Elem[MAX].link = -1;
}

// cursor-based helper functions
int allocSpace(Dictionary *D) {
    int newCell = D->avail;
    if (newCell != -1) {
        D->avail = D->Elem[D->avail].link;
    }
    return newCell;
}

void deallocSpace(Dictionary *D, int pointer) {
    D->Elem[pointer].link = D->avail;
    D->avail = pointer;
}

int hash(char elem) {
    return elem % MAX;
}

void insert(Dictionary *D, char elem) {
    if (search(*D, elem)) return;
    int hashed = hash(elem);
    if (D->Elem[hashed].data == EMPTY || D->Elem[hashed].data == DELETED) {
        D->Elem[hashed].data = elem;
    } else {
        // perform insert last cursor based style
        // ppi version
        int *trav = &(D->Elem[hashed].link);
        // perform 1 condition traversal
        for (trav; D->Elem[(*trav)].link != -1; trav = &(D->Elem[(*trav)].link)) {}

        // allocspace a new node:))
        int newNode = allocSpace(D);
        if (newNode != -1) {
            // perform insertion
            D->Elem[newNode].data = elem;
            D->Elem[(*trav)].link = newNode;
        }
    }
}

void deleteElem(Dictionary *D, char elem) {
    if (!search(*D, elem)) return;
    int hashed = hash(elem);
    // if first, then we need to swap first and last, then delete last
    // if not first, then delete pos, cursor-based style :)))

    // check if element is in the first stack thingy mabob
    if (D->Elem[hashed].data == elem) {
        int *trav = &(D->Elem[hashed].link);
        // perform 1 condition traversal
        for (trav; D->Elem[(*trav)].link != -1; trav = &(D->Elem[(*trav)].link)) {}
        D->Elem[hashed].data = D->Elem[(*trav)].data;
        deallocSpace(D, *trav);
        *trav = -1;
    } else {
        // perform 2 condition traversal
        int *trav = &(D->Elem[hashed].link);
        for (trav; D->Elem[(*trav)].link != -1 && D->Elem[(*trav)].data != elem; trav = &(D->Elem[(*trav)].link)) {}
        // perform delete pos cursor based style :VVV
        int temp = *trav;
        *trav = D->Elem[temp].link;
        deallocSpace(D, temp);
    }
}

int getIndex(Dictionary D, char elem) {
    // fix: missing return value when getIndex fails. 
    // modified to return -1
    if (!search(D, elem)) return -1;
    int hashed = hash(elem);
    // bug. this traversal does not chec if the current element that is hashed is the element we need to search
    // fix: initial conditional check that returns true if current index is what we're looking for
    if (D.Elem[hashed].data == elem) return hashed;
    int *trav = &(D.Elem[hashed].link);
    for (trav; D.Elem[(*trav)].link != -1 && D.Elem[(*trav)].data != elem; trav = &(D.Elem[(*trav)].link)) {}
    return *trav;
}

bool search(Dictionary D, char elem) {
    int hashed = hash(elem);
    // bug. this traversal does not chec if the current element that is hashed is the element we need to search
    // fix: initial conditional check that returns true if current index is what we're looking for
    if (D.Elem[hashed].data == elem) return true;
    int *trav = &(D.Elem[hashed].link);
    for (trav; D.Elem[(*trav)].link != -1 && D.Elem[(*trav)].data != elem; trav = &(D.Elem[(*trav)].link)) {}
    return *trav != -1;
}
