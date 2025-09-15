#include "cursorBased.h"

void initList(VirtualHeap *L) {
    L->list = -1;
    for (int i = 0; i < MAX; L->Elem[i].link = i - 1, i++) {}
    L->Avail = MAX - 1;
}

int allocSpace(VirtualHeap *L) {
    int newPointer = L->Avail;
    if (newPointer != -1) {
        L->Avail = L->Elem[newPointer].link;
    }
    return newPointer;
}

void deallocSpace(VirtualHeap *L, int pointer) {
    // pretty much just insert first
    // set the cell's next to avail,
    L->Elem[pointer].link = L->Avail;
    // then set avail to the pointer
    L->Avail = pointer;
}

void insertFirst(VirtualHeap *L, studtype student) {
    if (isFull(*L) != true) {
        int newNode = allocSpace(L);
        if (newNode != -1) {
            L->Elem[newNode].data = student;
            L->Elem[newNode].link = L->list;
            L->list = newNode;
        }
    }
}

void insertLast(VirtualHeap *L, studtype student) {
    if (isFull(*L) != true) {
        int newNode = allocSpace(L);
        if (newNode != -1) {
            L->Elem[newNode].data = student;
            // perform ppi (pointer to pointer to integer) traversal
            int *trav = &(L->list);
            for(trav; L->Elem[(*trav)].link != -1; trav = &(L->Elem[(*trav)].link)) {}
            L->Elem[(*trav)].link = newNode;
        }
    }
}

void insertPos(VirtualHeap *L, studtype student, int index) {
    if (isFull(*L) != true) {
        int newNode = allocSpace(L);
        if (newNode != -1) {
            L->Elem[newNode].data = student;
            // perform ppi (pointer to pointer to integer) traversal
            int *trav = &(L->list);
            int i = 0;
            for(trav, i; *trav != -1, i < index; trav = &(L->Elem[(*trav)].link), i++) {}
            if (i == index) {
                L->Elem[newNode].link = *trav;
                *trav = newNode;
            } else {
                deallocSpace(L, newNode);
            }
        }
    }
}

void deleteFirst(VirtualHeap *L) {
    if (isEmpty(*L) != true) {
        int temp = L->list;
        L->list = L->Elem[temp].link;
        deallocSpace(L, temp);
    }
}

void deleteLast(VirtualHeap *L) {
    if (isEmpty(*L) != true) {
        int *trav = &(L->list);
        for (trav; L->Elem[(*trav)].link != -1; trav = &(L->Elem[*trav].link)) {}
        deallocSpace(L, *trav);
        *trav = -1;
    }
}

void deletePos(VirtualHeap *L, int index) {
    if (isEmpty(*L) != true) {
        int *trav = &(L->list);
        int i = 0;
        for (trav, i; *trav != -1, i < index; trav = &(L->Elem[*trav].link), i++) {}
        if (i == index) {
            // do stuff
            int temp = *trav;
            *trav = L->Elem[temp].link;
            deallocSpace(L, temp);
        }
    }
}

void deleteStudent(VirtualHeap *L, char ID[]) {
    if (isEmpty(*L) != true) {
        int *trav = &(L->list);
        for (trav; *trav != -1 && strcmp(ID, L->Elem[*trav].data.ID) != 0; trav = &(L->Elem[*trav].link)) {}
        if (*trav != -1) {
            // do stuff
            int temp = *trav;
            *trav = L->Elem[temp].link;
            deallocSpace(L, temp);
        }
    }
}

bool findElem(VirtualHeap *L, char ID[]) {
    int *trav = &(L->list);
    for (trav; *trav != -1 && strcmp(ID, L->Elem[*trav].data.ID) != 0; trav = &(L->Elem[*trav].link)) {}
    return (*trav == -1) ? false : true;
}

bool isEmpty(VirtualHeap L) {
    return (L.list == -1) ? true : false;
}

bool isFull(VirtualHeap L) {
    return (L.Avail == -1) ? true : false;
}