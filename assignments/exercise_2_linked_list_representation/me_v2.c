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
    charList s1 = NULL;
    charList s2 = createCharList('a', 'b', 'b');
    charList s3 = createCharList('c', 'a', 'b');
    charList s4 = createCharList('a', 'b', 'c');
    charList s5 = createCharList('a', 'c', 'b');
    charList s6 = createCharList('c', 'a', 'b');
    charList s7 = createCharList('a', 'b', 'c');
    charList s8 = createCharList('a', 'c', 'b');
    charList s9 = createCharList('c', 'b', 'c');
    charList s10 = createCharList('c', 'c', 'c');

    char X = 'c';

    printf("Value of X = %c\n", X);
    printf("B.a '");
    printCharList(s1);
    printf("'? %s\n", findElem(s1, X) ? "True" : "False");
    printf("B.b '");
    printCharList(s2);
    printf("'? %s\n", findElem(s2, X) ? "True" : "False");
    printf("B.c '");
    printCharList(s3);
    printf("'? %s\n", findElem(s3, X) ? "True" : "False");
    deleteElem(&s3, X);
    printf("C.a.i ");
    printCharList(s3);
    deleteElem(&s4, X);
    printf("C.a.ii ");
    printCharList(s4);
    deleteElem(&s5, X);
    printf("C.a.iii ");
    printCharList(s5);
    deleteElem(&s2, X);
    printf("C.b ");
    printCharList(s2);
    deleteElem(&s1, X);
    printf("C.c ");
    printCharList(s1);
    deleteAllOccur(&s6, X);
    printf("D.a.i ");
    printCharList(s6);
    deleteAllOccur(&s7, X);
    printf("D.a.ii ");
    printCharList(s7);
    deleteAllOccur(&s8, X);
    printf("D.a.iii ");
    printCharList(s8);
    deleteAllOccur(&s2, X);
    printf("D.b ");
    printCharList(s2);
    deleteAllOccur(&s1, X);
    printf("D.c ");
    printCharList(s1);
    deleteAllOccur(&s9, X);
    printf("D.d ");
    printCharList(s9);
    deleteAllOccur(&s10, X);
    printf("D.e ");
    printCharList(s10);
    return 0;
}
charList createCharList(char a, char b, char c) {
    // fix: instead of using sizeof(charList) (which is 8 bytes since pointer)
    // use: malloc(sizeof(struct node))
    charList L = malloc(sizeof(struct node));
    charList trav = L;
    trav->elem = a;
    trav->link = malloc(sizeof(struct node));
    trav = trav->link;
    trav->elem = b;
    trav->link = malloc(sizeof(struct node));
    trav = trav->link;
    trav->elem = c;
    trav->link = NULL;
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
    charList trav = L;
    while (trav != NULL && !flag) {
        if (trav->elem == X) {
            flag = true;
        }
        trav = trav->link;
    }
    return flag;
}
// work on this in a bit
// dapat double pointer diay ni
void deleteElem(charList *L, char X) {
    while (*L != NULL && (*L)->elem != X) {
        L = &(*L)->link;
    }
    // fix: *L instead of (*L)->link since it's already pointing to the thingyy
    if (*L != NULL) {
        charList tmp = *L;
        *L = tmp->link;
        free(tmp);
    }
}
void deleteAllOccur(charList *L, char X) {
    while (*L != NULL) {
        // fix: (*L)->elem instead of link
        if ((*L)->elem == X) {
            charList tmp = *L;
            *L = tmp->link;
            free(tmp);
        } else {
            L = &(*L)->link;
        }
    }
}