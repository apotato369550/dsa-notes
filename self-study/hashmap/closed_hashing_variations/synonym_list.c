#include "synonym_list.h"

void initializeDictionary(Dictionary *D) {
    // fix: change '==' into '='
    for (int i = 0; i < MAX; i++, (*D).Elem[i] = EMPTY) {}
    (*D).last = MAX;
}

int hash(char elem) {
    return elem % MAX;
}

void insert(Dictionary *D, char elem) {
    if (search((*D), elem)) return;
    int hashed = hash(elem);
    if ((*D).Elem[hashed] != EMPTY) {
        // bug: MAX instead of MAX * 2, when MAX * 2 is the true size of the list and is the max capacity for the extended list
        // fix: changed 'MAX' into 'MAX * 2'
        if ((*D).last < MAX * 2) {
            (*D).Elem[(*D).last] = elem;
            (*D).last += 1;
        } else {
            printf("Unable to insert into dictionary. Dictionary full.\n");
        }
    } else {
        (*D).Elem[hashed] = elem;
    }
}

// continue here haha
void deleteElem(Dictionary *D, char elem) {
    if (!search((*D), elem)) return;
    int hashed = hash(elem);
    if ((*D).Elem[hashed] == elem) {
        // bug (but not really): deleted marked as EMPTY instead of DELETED
        // fix: changed 'EMPTY' to 'DELETED'
        (*D).Elem[hashed] = DELETED;
    } else {
        // linear search over adt
        // 2 cond traversal
        int i;
        for (i = MAX; i < (*D).last && (*D).Elem[i] != elem; i++) {}
        if (i < MAX) {
            // if i < max we found it. just delete it. order doesn't matter
            (*D).Elem[i] = (*D).Elem[--(*D).last];
        }
        // 1 - 0
        // 2 - 2
        // 3 - 2
        // empty - 3
        // last is count p much
        // count = 3
    }

    // change this mechanism
}

bool search(Dictionary D, char elem) {
    // wait this mechanism needs to be replaced lol
    int hashed = hash(elem);
    if (D.Elem[hashed] == elem) return true; 
    // search adt here
    int i;
    for (i = MAX; i < D.last && D.Elem[i] != elem; i++) {}
    return i != D.last;
}


int getIndex(Dictionary D, char elem) {
    int hashed = hash(elem);
    if (D.Elem[hashed] == elem) return hashed; 
    // search adt here
    int i;
    for (i = MAX; i < D.last && D.Elem[i] != elem; i++) {}
    return (i < D.last) ? i : -1;

}

void printDictionary(Dictionary D) {
    printf("\n---PRINTING DICTIONARY---\n");
    for (int i = 0; i < MAX; i++) {
        printf("[%d] = %c\n", i, D.Elem[i]);
    }
    printf("\n---DICTIONARY END---\n");
}