#include <stdio.h>

#include "computer_word.h"

void initSet(SET *A) {
    *A = 0;
}

void displaySet(SET A, char *name) {
    printf("%s = {");
    for (int i = 0; i < N_BITS; i++) {
        SET mask = 1 << i;
        if ((int) A & (int) mask != 0) {
            printf("%d", i + 1);
        }
    }
    printf("}");
}

void insert(SET *A, int elem) {
    SET mask = 1 << elem;
    *A = (*A) | mask;
}

bool isMember(SET A, int elem) {
    if (elem >= N_BITS) return false;
    SET mask = 1 << elem;
    return ((A & mask) == 0) ? false : true;
}

void deleteElem(SET *A, int elem) {
    if (isMember(*A, elem) != true) return;
    SET mask = 1 << elem;
    *A = (*A) ^ mask;
}

SET unionSet(SET A, SET B) {
    return A | B;
}

SET intersectionSet(SET A, SET B) {
    return A & B;
}

SET differenceSet(SET A, SET B) {
    // i forgot the formula for this lol
    // u = 1, 2, 3, 4, 5, 6
    // a = 1, 2, 3
    // b = 2, 3, 4
    // ~a = 4, 5, 6
    // ~b = 1, 5, 6
    // 

    // correct bani siya? lez check lmao
    return (~B) & A; 
}