#include "open_hashing.h"
// fix: forgot to import stdlib.h lmao

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
    if (search(D, elem) == true) return;
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

void deleteElem(Dictionary D, char elem) {
    int hashed_index = hash(elem);
    // changed 'D[elem]' to 'D[hashed_index]' 
    if (D[hashed_index] == NULL) return;
    NodePointer *trav;
    for (trav = &(D[hashed_index]); *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link) {}

    if (*trav != NULL) {
        Node *temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}
bool search(Dictionary D, char elem) {
    int hashed_index = hash(elem);
    // changed 'D[elem]' to 'D[hashed_index]' 
    if (D[hashed_index] == NULL) return;
    NodePointer *trav;
    for (trav = &(D[hashed_index]); *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link) {}

    if (*trav != NULL) {
        return true;
    } else {
        return false;
    }
}

int getIndex(Dictionary D, char elem) {
    return hash(elem);
}

void printDictionary(Dictionary D) {
    printf("\n---PRINTING DICTIONARY---\n");
    for (int i = 0; i < MAX_ENTRIES; i++) {
        printf("[%d] = ", i);
        NodePointer *trav;
        for (trav = &(D[i]); *trav != NULL && (*trav); trav = &(*trav)->link) {
            printf("%c ", (*trav)->data);
            if ((*trav)->link != NULL) {
                printf("-> ");
            }
        }
        printf("\n");
    }
    printf("\n---DICTIONARY END---\n");
}
