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
    // bug: didn't check if valid index
    // fix: check if valid index
    if (isFull(*L) != true && index >= 0 && index <= L->count) {
        int i;
        for (i = L->count; i > index; L->Elem[i] = L->Elem[i - 1], i--) {}

        // bug: prevents insertion at end of list
        // fix: replace i < L->count with i <= L->count 
        if (i <= L->count) {
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
    // bug: failed to check bounds for index
    // fix: check if index >= 0 and index < L->count
    // < L->count and not <= because it's not insertion
    if (isEmpty(*L) != true && index >= 0 && index < L->count) {
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
        for (i = 0; i < L->count && strcmp(ID, L->Elem[i].ID) != 0; i++) {}

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
    // bug: comma instead of &&
    for (i = 0; i < L->count && strcmp(ID, L->Elem[i].ID) != 0; i++) {}
    return (i < L->count) ? true : false;
}

bool isEmpty(ArrayList L) {
    return L.count == 0;
}

bool isFull(ArrayList L) {
    return L.count >= MAX;
}


void displayList(ArrayList L) {
    if (isEmpty(L)) {
        printf("List is empty.\n");
        return;
    }
    
    printf("\nCurrent List:\n");
    for (int i = 0; i < L.count; i++) {
        printf("%d. %s %c %s - ID: %s, Year: %d, Course: %s\n", 
               i+1, L.Elem[i].name.firstName, L.Elem[i].name.MI, 
               L.Elem[i].name.lastName, L.Elem[i].ID, 
               L.Elem[i].year, L.Elem[i].course);
    }
    printf("\n");
}
