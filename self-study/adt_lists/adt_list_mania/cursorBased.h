#ifndef ARRAYLIST
#define ARRAYLIST

#include <string.h>
#include <stdbool.h>
#include "studtype.h"

#define MAX 10
typedef struct {
    studtype Elem[MAX];
    int Avail;
    int list;
} VirtualHeap;

void initList(VirtualHeap *L);

void insertFirst(VirtualHeap *L, studtype student);
void insertLast(VirtualHeap *L, studtype student);
void insertPos(VirtualHeap *L, studtype student, int index);

void deleteFirst(VirtualHeap *L);
void deleteLast(VirtualHeap *L);
void deletePos(VirtualHeap *L, int index);

void deleteStudent(VirtualHeap *L, char ID[]);
bool findElem(VirtualHeap *L, char ID[]);

bool isEmpty(VirtualHeap L);
bool isFull(VirtualHeap L);

#endif