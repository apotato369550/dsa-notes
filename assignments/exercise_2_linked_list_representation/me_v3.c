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

int main () {
    charList s1 = NULL;
    charList s2 = createCharList('a', 'b', 'b');
    charList s3 = createCharList('c', 'a', 'b');
    char X = 'c';
    printf("Value of X = %c\n", X);
    printf("B.a X present in '");
    printCharList(s1);
    printf("'? %s\n", findElem(s1, X) ? "True" : "False");
    printf("B.b X present in '");
    printCharList(s2);
    printf("'? %s\n", findElem(s2, X) ? "True" : "False");
    printf("B.c X present in '");
    printCharList(s3);
    printf("'? %s\n", findElem(s3, X) ? "True" : "False");
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