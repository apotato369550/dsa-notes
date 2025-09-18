#ifndef ARRAYLIST
#define ARRAYLIST

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "studtype.h"

#define MAX 10
typedef struct {
    studtype Elem[MAX];
    int count;
} ArrayList, List;

void initList(ArrayList *L);

void insertFirst(ArrayList *L, studtype student);
void insertLast(ArrayList *L, studtype student);
void insertPos(ArrayList *L, studtype student, int index);

void deleteFirst(ArrayList *L);
void deleteLast(ArrayList *L);
void deletePos(ArrayList *L, int index);

void deleteStudent(ArrayList *L, char ID[]);
bool findElem(ArrayList *L, char ID[]);
bool isEmpty(ArrayList L);
bool isFull(ArrayList L);

// bug: declared isEmpty and isFull twice lol

// MAKE DISPLAYLIST
void displayList(ArrayList L);

#endif