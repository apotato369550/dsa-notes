#include "multi_word.h"

void initSet(SET A) {
    for (int i = 0; i < N_WORDS; i++) {
        A[i] = 0;
    }
}

void displaySet(SET A, char *name) {
    printf("%s = {");
    for (int i = 0; i < N_WORDS; i++) {
        WORD currentWord = A[i];
        for (int j = 0; j < N_BITS; j++) {
            WORD mask = 1 << i;
            if ((currentWord & mask) != 0) {
                printf("%d, ", (j + (i * N_BITS)));
            }
        }
    }
    printf(" }");
}

void insert(SET A, int elem) {
    int word = A[floor(elem / N_WORDS)];
    WORD mask = 1 << (elem % N_WORDS);
    A[floor(elem / N_WORDS)] = word | mask;
}

bool isMember(SET A, int elem) {
    int word = A[floor(elem / N_WORDS)];
    WORD mask = 1 << (elem % N_WORDS);
    return word & mask;
}

void deleteElem(SET A, int elem) {
    int word = A[floor(elem / N_WORDS)];
    WORD mask = 1 << (elem % N_WORDS);
    A[floor(elem / N_WORDS)] = word & mask;
}

SET *unionSet(SET A, SET B) {
    SET *C = (SET*)malloc(sizeof(SET));

    for (int i = 0; i < N_WORDS; i++) {
        (*C)[i] = A[i] | B[i];
    }

    return C;
}

SET *intersectionSet(SET A, SET B) {
    SET *C = (SET*)malloc(sizeof(SET));

    for (int i = 0; i < N_WORDS; i++) {
        (*C)[i] = A[i] & B[i];
    }

    return C;
}

SET *differenceSet(SET A, SET B) {
    SET *C = (SET*)malloc(sizeof(SET));

    for (int i = 0; i < N_WORDS; i++) {
        (*C)[i] = A[i] & (~B[i]);
    }

    return C;
}