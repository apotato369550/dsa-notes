#ifndef COMPUTER_WORD_H
#define COMPUTER_WORD_H

#include <stdbool.h>

// OMG. SIZEOF RETURNS BYTES, NOT BITS??
#define N_BITS sizeof(unsigned int) * 8
#define N_WORDS 4

typedef unsigned int WORD;
typedef WORD SET[N_WORDS];

void initSet(SET A);
void displaySet(SET A, char *name);
void insert(SET A, int elem);
bool isMember(SET A, int elem);
void deleteElem(SET A, int elem);
SET *unionSet(SET A, SET B);
SET *intersectionSet(SET A, SET B);
SET *differenceSet(SET A, SET B);

#endif