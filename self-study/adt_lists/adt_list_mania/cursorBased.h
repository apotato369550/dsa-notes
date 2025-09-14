#ifndef CURSORBASED
#define CURSORBASED

#include <string.h>
#include <stdbool.h>
#include "studtype.h"

#define MAX 10

typedef struct {
    studtype data;
    int link;
} nodetype;

typedef struct {
    nodetype Elem[MAX];
    int Avail;
    int list;
} VirtualHeap;

void initList(VirtualHeap *L);
int allocSpace(VirtualHeap *L);
void deallocSpace(VirtualHeap *L, int pointer);

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

// make this lol
void displayList(VirtualHeap *L);

#endif