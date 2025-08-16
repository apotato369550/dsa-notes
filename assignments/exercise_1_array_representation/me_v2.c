#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10

typedef struct charList {
    char elem[MAX];
    int count;
} charList;

bool findElem(charList L, char X);
void deleteElem(charList *L, char X);
void deleteAllOccur(charList *L, char X);

int main() {
    charList s1;
    s1.elem[0] = '\0';
    s1.count = 0;
    charList s2;
    strcpy(s2.elem, "dracula");
    s2.count = strlen(s2.elem);
    charList s3;
    strcpy(s3.elem, "belmont");
    s3.count = strlen(s3.elem);
    charList s4;
    strcpy(s4.elem, "castlevania");
    s4.count = strlen(s4.elem);
    charList s5;
    strcpy(s5.elem, "isaac");
    s5.count = strlen(s5.elem);
    charList s6;
    strcpy(s6.elem, "calculator");
    s6.count = strlen(s6.elem);
    charList s7;
    strcpy(s7.elem, "berelac");
    s7.count = strlen(s7.elem);
    charList s8;
    strcpy(s8.elem, "occurence");
    s8.count = strlen(s8.elem);
    char X = 'c';
    printf("Value of X = %c\n", X);
    printf("B.a '%s'?: %s\n", s1.elem, findElem(s1, X) ? "True" : "False");
    printf("B.b '%s'?: %s\n", s2.elem, findElem(s2, X) ? "True" : "False");
    printf("B.c '%s'?: %s\n", s3.elem, findElem(s3, X) ? "True" : "False");
    deleteElem(&s4, X);
    printf("C.a.i %s\n", s4.elem);
    deleteElem(&s5, X);
    printf("C.a.ii %s\n", s5.elem);
    deleteElem(&s2, X);
    printf("C.a.iii %s\n", s2.elem);
    deleteElem(&s3, X);
    printf("C.b %s\n", s3.elem);
    deleteElem(&s1, X);
    printf("C.c %s\n", s1.elem);
    deleteAllOccur(&s6, X);
    printf("D.a.i %s\n", s6.elem);
    deleteAllOccur(&s7, X);
    printf("D.a.ii %s\n", s7.elem);
    deleteAllOccur(&s8, X);
    printf("D.a.iii %s\n", s8.elem);
    deleteAllOccur(&s3, X);
    printf("D.b %s\n", s3.elem);
    deleteAllOccur(&s1, X);
    printf("D.c %s\n", s1.elem);
    return 0;
}
bool findElem(charList L, char X) {
    bool flag = false;
    for (int ndx = 0; ndx < L.count && !flag; ndx++) {
        if (L.elem[ndx] == X) {
            flag = true;
        }
    }
    return flag;
}
void deleteElem(charList *L, char X) {
    for (int ndx = 0; ndx < L->count; ndx++) {
        if (L->elem[ndx] == X) {
            for (int ndy = ndx; ndy < L->count - 1; ndy++) {
                L->elem[ndy] = L->elem[ndy + 1];
            }
            L->count--;
            L->elem[L->count] = '\0';
            return;
        }
    }
}
void deleteAllOccur(charList *L, char X) {
    for (int ndx = 0; ndx < L->count; ndx++) {
        if (L->elem[ndx] == X) {
            for (int ndy = ndx; ndy < L->count - 1; ndy++) {
                L->elem[ndy] = L->elem[ndy + 1];
            }
            L->count--;
            L->elem[L->count] = '\0';
            ndx--;
        }
    }
}