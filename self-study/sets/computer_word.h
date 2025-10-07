#ifndef COMPUTER_WORD_H
#define COMPUTER_WORD_H

#include <stdbool.h>

#define N_BITS 8

typedef unsigned char SET;

void initSet(SET *A);
void displaySet(SET A, char *name);
void insert(SET *A, int elem);
bool isMember(SET A, int elem);
void deleteElem(SET *A, int elem);
SET unionSet(SET A, SET B);
SET intersectionSet(SET A, SET B);
SET differenceSet(SET A, SET B);

#endif