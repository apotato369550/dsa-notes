#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "studtype.h"

#define MAX 10

typedef struct Node {
    studtype data;
    struct Node *link;
} *LinkedList, Node, *List;

void initList(LinkedList *L);

void insertFirst(LinkedList *L, studtype student);
void insertLast(LinkedList *L, studtype student);
void insertPos(LinkedList *L, studtype student, int index);

void deleteFirst(LinkedList *L);
void deleteLast(LinkedList *L);
void deletePos(LinkedList *L, int index);

void deleteStudent(LinkedList *L, char ID[]);
bool findElem(LinkedList *L, char ID[]);

bool isEmpty(LinkedList L);
bool isFull(LinkedList L);

// make this lol
// should be pass by value instead of pass by reference
void displayList(LinkedList L);

#endif