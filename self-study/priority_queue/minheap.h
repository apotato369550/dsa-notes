#ifndef MINHEAP
#define MINHEAP

#include <limits.h>
#include <math.h>
#include <stdbool.h>
// ???
#include <<heap.h>

// todo: modify to include is_POT() for minheap

void initialize(Minheap *M);
void insert(Minheap *M, int x);
// bug: wrong header 'deleteMax' instead of 'deleteMin'
// fix: changed 'deleteMax' to 'deleteMin'
int deleteMin(Minheap *M);
void makeNull(Minheap *M);
void heapifyUp(Minheap *M, int i);
void heapifyDown(Minheap *M, int i);


#endif