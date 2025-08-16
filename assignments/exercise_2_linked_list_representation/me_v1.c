#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char elem;
    struct node *link;
} *charList; 

charList createCharList(char a, char b, char c);
void printCharList(charList L);
bool findElem(charList L, char X);
void deleteElem(charList *L, char X);
void deleteAllOccur(charList *L, char X);

int main () {
    charList empty = NULL;
    charList notFound = createCharList('a', 'b', 'b');
    charList first1 = createCharList('c', 'a', 'b');
    charList last1 = createCharList('a', 'b', 'c');
    charList middle1 = createCharList('a', 'c', 'b');
    charList first2 = createCharList('c', 'a', 'b');
    charList last2 = createCharList('a', 'b', 'c');
    charList middle2 = createCharList('a', 'c', 'b');
    charList two = createCharList('c', 'b', 'c');
    charList all = createCharList('c', 'c', 'c');

    char X = 'c';

    printf("Value of X = %c\n", X);

    printf("B.a '");
    printCharList(empty);
    printf("'? %s\n", findElem(empty, X) ? "True" : "False");

    printf("B.b '");
    printCharList(notFound);
    printf("'? %s\n", findElem(notFound, X) ? "True" : "False");

    printf("B.c '");
    printCharList(first1);
    printf("'? %s\n", findElem(first1, X) ? "True" : "False");
    
    // continue from here
    deleteElem(&first1, X);
    printf("C.a.i ");
    printCharList(first1);

    deleteElem(&last1, X);
    printf("C.a.ii ");
    printCharList(last1);

    deleteElem(&middle1, X);
    printf("C.a.iii ");
    printCharList(middle1);

    deleteElem(&notFound, X);
    printf("C.b ");
    printCharList(notFound);

    deleteElem(&empty, X);
    printf("C.c ");
    printCharList(empty);

    deleteAllOccur(&first2, X);
    printf("D.a.i ");
    printCharList(first2);

    deleteAllOccur(&last2, X);
    printf("D.a.ii ");
    printCharList(last2);

    deleteAllOccur(&middle2, X);
    printf("D.a.iii ");
    printCharList(middle2);

    deleteAllOccur(&notFound, X);
    printf("D.b ");
    printCharList(notFound);

    deleteAllOccur(&empty, X);
    printf("D.c ");
    printCharList(empty);
    return 0;
}

charList createCharList(char a, char b, char c) {
    charList L = malloc(sizeof(charList));
    charList trav = L;
    trav->elem = a;
    trav->link = malloc(sizeof(charList));
    trav = trav->link;
    trav->elem = b;
    trav->link = malloc(sizeof(charList));
    trav = trav->link;
    trav->elem = c;
    return L;
}

void printCharList(charList L) {
    while (L != NULL) {
        printf("%c", L->elem);
        L = L->link;
    }
    printf("\n");
}

bool findElem(charList L, char X) {
    bool flag = false;
    while (L != NULL && !flag) {
        if (L->elem == X) {
            flag = true;
        }
        L = &(*L->link);
    }
    return flag;
}
// work on this in a bit
// dapat double pointer diay ni
void deleteElem(charList *L, char X) {
    if (L == NULL || *L == NULL) {
        return;
    }
    if ((*L)->elem == X) {
        return;
    }
    while ((*L)->link != NULL) {
        if ((*L)->link->elem == X) {
            // perform magic
            charList del = (*L)->link;
            (*L)->link = del->link;
            free(del);
            return;
        }
        L = &(*L)->link;
    }
}
void deleteAllOccur(charList *L, char X) {
    if (L == NULL || *L == NULL) {
        return;
    }
    if ((*L)->elem == X) {
        return;
    }
    while ((*L)->link != NULL) {
        int flag = 0;
        while ((*L)->link->elem == X) {
            // perform magic
            charList del = (*L)->link;
            (*L)->link = del->link;
            free(del);
        }
        L = &(*L)->link;
    }
}