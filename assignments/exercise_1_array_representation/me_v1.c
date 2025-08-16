#include <stdio.h>
// use booleans
#include <stdbool.h>
#include <string.h>

// max number of elements in array
#define MAX 10

// it's a static array, not a dynamic one
typedef struct charList {
    char elem[MAX];
    int count;
} charList;

bool findElem(charList L, char X);
void deleteElem(charList *L, char X);
void deleteAllOccur(charList *L, char X);

int main() {
    // declare and initialize variables

    // empty case to be used in all three functions
    charList emptyCharList;
    emptyCharList.count = 0;

    // cases used in first two functions
    charList isPresent;
    strcpy(isPresent.elem, "dracula");
    isPresent.count = strlen(isPresent.elem);

    charList isNotPresent;
    strcpy(isNotPresent.elem, "belmont");
    isNotPresent.count = strlen(isNotPresent.elem);

    charList firstElement;
    strcpy(firstElement.elem, "castlevania");
    firstElement.count = strlen(firstElement.elem);

    charList lastElement;
    strcpy(lastElement.elem, "isaac");
    lastElement.count = strlen(lastElement.elem);

    // cases used in last (delete all occurences function)
    // first position:
    charList firstElement2;
    strcpy(firstElement2.elem, "calculator");
    firstElement2.count = strlen(firstElement2.elem);

    charList lastElement2;
    strcpy(lastElement2.elem, "berelac");
    lastElement2.count = strlen(lastElement2.elem);

    charList middleElement;
    strcpy(middleElement.elem, "occurence");
    middleElement.count = strlen(middleElement.elem);


    char X = 'c';

    printf("B.a Is '%c' present in string '%s'?: %s\n", X, emptyCharList.elem, findElem(emptyCharList, X) ? "True" : "False");
    printf("B.b Is '%c' present in string '%s'?: %s\n", X, isPresent.elem, findElem(isPresent, X) ? "True" : "False");
    printf("B.c Is '%c' present in string '%s'?: %s\n", X, isNotPresent.elem, findElem(isNotPresent, X) ? "True" : "False");

    printf("C.a.i Deleting first occurence of '%c' in '%s': ", X, firstElement.elem);
    deleteElem(&firstElement, X);
    printf("%s\n", firstElement.elem);

    
    printf("C.a.ii Deleting first occurence of '%c' in '%s': ", X, lastElement.elem);
    deleteElem(&lastElement, X);
    printf("%s\n", lastElement.elem);

    
    printf("C.a.iii Deleting first occurence of '%c' in '%s': ", X, isPresent.elem);
    deleteElem(&isPresent, X);
    printf("%s\n", isPresent.elem);

    printf("C.b Deleting first occurence of '%c' in '%s': ", X, isNotPresent.elem);
    deleteElem(&isNotPresent, X);
    printf("%s\n", isNotPresent.elem);

    
    printf("C.c Deleting first occurence of '%c' in '%s': ", X, emptyCharList.elem);
    deleteElem(&emptyCharList, X);
    printf("%s\n", emptyCharList.elem);

    
    printf("D.a.i Deleting all occurences of '%c' in '%s': ", X, firstElement2.elem);
    deleteAllOccur(&firstElement2, X);
    printf("%s\n", firstElement2.elem);

    
    printf("D.a.ii Deleting all occurences of '%c' in '%s': ", X, lastElement2.elem);
    deleteAllOccur(&lastElement2, X);
    printf("%s\n", lastElement2.elem);

    
    printf("D.a.iii Deleting all occurences of '%c' in '%s': ", X, middleElement.elem);
    deleteAllOccur(&middleElement, X);
    printf("%s\n", middleElement.elem);

    printf("D.b Deleting all occurences of '%c' in '%s': ", X, isNotPresent.elem);
    deleteAllOccur(&isNotPresent, X);
    printf("%s\n", isNotPresent.elem);


    printf("D.c Deleting all occurences of '%c' in '%s': ", X, emptyCharList.elem);
    deleteAllOccur(&emptyCharList, X);
    printf("%s\n", emptyCharList.elem);
    
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