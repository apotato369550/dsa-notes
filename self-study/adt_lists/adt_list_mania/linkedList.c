#include "linkedList.h"

void initList(LinkedList *L) {
    *L = NULL;
}

void insertFirst(LinkedList *L, studtype student) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = student;
        newNode->link = *L;
        *L = newNode;
    }
}

void insertLast(LinkedList *L, studtype student) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = student;
        newNode->link = NULL;
        LinkedList *trav = L;
        for (trav; *trav != NULL; trav = &(*trav)->link) {}
        *trav = newNode;
    }
}

void insertPos(LinkedList *L, studtype student, int index) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = student;
        LinkedList *trav = L;
        int i;
        for (trav, i; *trav != NULL, i < index; trav = &(*trav)->link, i++) {}
        if (i == index) {
            newNode->data = student;
            newNode->link = *trav;
            *trav = newNode;
        } else {
            free(newNode);
        }
    }
}

void deleteFirst(LinkedList *L) {
    if (isEmpty(*L) != true) {
        Node *temp = *L;
        *L = temp->link;
        free(temp);
    }
}
void deleteLast(LinkedList *L) {
    if (isEmpty(*L) != true) {
        LinkedList *trav = L;
        for (trav; (*trav)->link != NULL; trav = &(*trav)->link) {}
        free(*trav);
        *trav = NULL;
    }
}
void deletePos(LinkedList *L, int index) {
    if (isEmpty(*L) != true) {
        LinkedList *trav = L;
        int i = 0;
        for (trav, i; *trav != NULL, i < index; trav = &(*trav)->link, i++) {}
        if (i == index) {
            Node *temp = *trav;
            *trav = temp->link;
            free(temp);
        }
    }
}

void deleteStudent(LinkedList *L, char ID[]) {
    if (isEmpty(*L) != true) {
        LinkedList *trav = L;
        for (trav; (*trav)->link != NULL, strcmp(ID, (*trav)->data.ID) != 0; trav = &(*trav)->link) {}
        if (*trav != NULL) {
            Node *temp = *trav;
            *trav = temp->link;
            free(temp);
        }
    }
}

bool findElem(LinkedList *L, char ID[]) {
    LinkedList *trav = L;
    for (trav; *trav != NULL && strcmp(ID, (*trav)->data.ID) != 0; trav = &(*trav)->link) {}
    return (*trav == NULL) ? false : true;
}

bool isEmpty(LinkedList L) {
    return (L == NULL) ? true : false;
}

bool isFull(LinkedList L) {
    return false;
}