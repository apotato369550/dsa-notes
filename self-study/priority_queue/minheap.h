#ifndef MINHEAP
#define MINHEAP

#define MAX 23

typedef int Minheap[23];

void initialize(Minheap M);
void insert(Minheap M, int x);
int deleteMax(Minheap M);
void makeNull(Minheap M);


#endif