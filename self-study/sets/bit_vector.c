#include "bit_vector.h"
#include <stdio.h>
#include <stdlib.h>

void initSet(SET A) {
    for (int i = 0; i < N_ELEM; i++) {
        A[i] = false;
    }
}

void displaySet(SET A, char *name) {
    printf("%s = {");
    bool first = true;
    for (int i = 0; i < N_ELEM; i++) {
        // minor fix: fixed set printing
        if (A[i] == true) {
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("}");
}

void insert(SET A, int elem) {
    if (elem >= N_ELEM) return;
    A[elem] = true;
}

bool isMember(SET A, int elem) {
    if (elem >= N_ELEM) return false;
    return A[elem];
}

void deleteElem(SET A, int elem) {
    if (elem >= N_ELEM) return;
    A[elem] = false;
}

SET *unionSet(SET A, SET B) {
    SET *C = (SET*)malloc(sizeof(SET));
    for (int i = 0; i < N_ELEM; i++) {
        (*C)[i] = A[i] || B[i];
    }
    return C;
}

SET *intersectionSet(SET A, SET B) {
    SET *C = (SET*)malloc(sizeof(SET));
    for (int i = 0; i < N_ELEM; i++) {
        (*C)[i] = A[i] && B[i];
    }
    return C;
}
SET *differenceSet(SET A, SET B) {
    SET *C = (SET*)malloc(sizeof(SET));
    for (int i = 0; i < N_ELEM; i++) {
        (*C)[i] = A[i] && !B[i];
    }
    return C;
}
