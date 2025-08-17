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
    char X = 'c';
    printf("Value of X = %c\n", X);
    printf("B.a X present in '%s'?: %s\n", s1.elem, findElem(s1, X) ? "True" : "False");
    printf("B.b X present in '%s'?: %s\n", s2.elem, findElem(s2, X) ? "True" : "False");
    printf("B.c X present in '%s'?: %s\n", s3.elem, findElem(s3, X) ? "True" : "False");
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