#include "arraylist.h"

void initList(ArrayList *L) {
    L->count = 0;
}

void insertFirst(ArrayList *L, studtype student) {
    if (isFull(*L) != true) {
        for (int i = L->count; i > 0; L->Elem[i] = L->Elem[i - 1], i--) {}
        L->Elem[0] = student;
        L->count++;
    }
}

void insertLast(ArrayList *L, studtype student) {
    if (isFull(*L) != true) {
        L->Elem[L->count++] = student;
    }
}

void insertPos(ArrayList *L, studtype student, int index) {
    if (isFull(*L) != true) {
        int i;
        for (i = L->count; i > index; L->Elem[i] = L->Elem[i - 1], i--) {}
        if (i < L->count) {
            L->Elem[index] = student;
            L->count++;
        }
    }
}

void deleteFirst(ArrayList *L) {
    if (isEmpty(*L) != true) {
        int length = L->count - 1;
        for (int i = 0; i < length; L->Elem[i] = L->Elem[i + 1], i++) {}
        L->count--;
    }
}

void deleteLast(ArrayList *L) {
    if (isEmpty(*L) != true) {
        L->count--;
    }
}

void deletePos(ArrayList *L, int index) {
    if (isEmpty(*L) != true) {
        int length = L->count - 1;
        for (int i = index; i < length; L->Elem[i] = L->Elem[i + 1], i++) {}
        L->count--;
    }
}

void deleteStudent(ArrayList *L, char ID[]) {
    if (isEmpty(*L) != true) {
        // 2 condition traversal
        int i;
        // fix: L->Elem->ID should be L->Elem[i].ID
        for (i = 0; i < L->count, strcmp(ID, L->Elem[i].ID) != 0; i++) {}

        // fix: change >= to <. my mistake. 
        // it should delete if the for loop was stopped abruptly,
        // hence i being less than count
        if (i < L->count) {
            deletePos(L, i);
        }
    }
}
bool findElem(ArrayList *L, char ID[]) {
    int i;
    for (i = 0; i < L->count, strcmp(ID, L->Elem[i].ID) != 0; i++) {}
    return (i < L->count) ? true : false;
}

bool isEmpty(ArrayList L) {
    return L.count == 0;
}

bool isFull(ArrayList L) {
    return L.count >= MAX;
}