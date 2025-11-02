#ifndef MAXHEAP
#define MAXHEAP

#define MAX 11

typedef int Maxheap[23];

void initialize(Maxheap M);
void insert(Maxheap M, int x);
int deleteMax(Maxheap M);
void makeNull(Maxheap M);


#endif