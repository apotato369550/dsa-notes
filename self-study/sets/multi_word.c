#include "multi_word.h"

void initSet(SET A) {
    for (int i = 0; i < N_WORDS; i++) {
        A[i] = 0;
    }
}

void displaySet(SET A, char *name) {
    printf("%s = {");
    bool first = true;
    for (int i = 0; i < N_WORDS; i++) {
        WORD currentWord = A[i];
        for (int j = 0; j < N_BITS; j++) {
            // bug: used i instead of j for moving the bits in the mask
            // fix: replace i with j
            WORD mask = 1 << j;
            if ((currentWord & mask) != 0) {
                if (!first) printf(", ");
                printf("%d", (j + (i * N_BITS)));
                first = false;
            }
        }
    }
    printf(" }");
}

void insert(SET A, int elem) {
    // bug: dividing using N_WORDS instead of N_BITS
    // fix: replacing N_WORDS with N_BITS
    int word = A[floor(elem / N_BITS)];
    WORD mask = 1 << (elem % N_BITS);
    A[floor(elem / N_WORDS)] = word | mask;
}

bool isMember(SET A, int elem) {
    // bug: dividing using N_WORDS instead of N_BITS
    // fix: replacing N_WORDS with N_BITS
    int word = A[floor(elem / N_BITS)];
    WORD mask = 1 << (elem % N_BITS);
    return word & mask;
}

void deleteElem(SET A, int elem) {
    // bug: dividing using N_WORDS instead of N_BITS
    // fix: replacing N_WORDS with N_BITS
    int word = A[floor(elem / N_BITS)];
    WORD mask = 1 << (elem % N_BITS);

    // bug: using hte wrong bitwise operations.
    // deletion should be done by word & ~mask, not word & mask
    // fix: changed (word & mask) to (word & ~mask)
    A[floor(elem / N_BITS)] = word & ~mask;
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