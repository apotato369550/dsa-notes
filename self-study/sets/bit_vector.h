#ifndef BIT_VECTOR
#define BIT_VECTOR

#include <stdbool.h>

#define N_ELEM 8

typedef bool SET[N_ELEM];

void initSet(SET A);
void displaySet(SET A, char *name);
// fix: changed '*A' to 'A' because SET is already an array
void insert(SET A, int elem);
bool isMember(SET A, int elem);
void deleteElem(SET A, int elem);
SET *unionSet(SET A, SET B);
SET *intersectionSet(SET A, SET B);
SET *differenceSet(SET A, SET B);

#endif