#ifndef QUADRATIC_HASHING
#define QUADRATIC_HASHING

#include <stdbool.h>

#define MAX 11
#define EMPTY '*'
#define DELETED '?'

typedef char Dictionary[MAX];

void initializeDictionary(Dictionary D);
int hash(char elem);
void insert(Dictionary D, char elem);
void deleteElem(Dictionary D, char elem);
bool search(Dictionary D, char elem);
int getIndex(Dictionary D, char elem);
void printDictionary(Dictionary D);

#endif