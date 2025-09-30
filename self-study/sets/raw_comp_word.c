#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N_BITS 8

typedef unsigned char SET;

void initSet(SET *A);
// alter
void displaySet(SET A, char *name);
void insert(SET *A, int elem);
bool member(SET A, int elem);
void deleteElem(SET *A, int elem);
SET *unionSet(SET A, SET B, char set1Name[], char set2Name[]);
SET *intersection(SET A, SET B, char set1Name[], char set2Name[]);
SET *difference(SET A, SET B, char set1Name[], char set2Name[]);

int main() {
	SET U, A, B;
	
	initSet(&U);
	initSet(&A);
	initSet(&B);
	
	// display sets after initialization
	printf("Sets after initializing: \n");
	displaySet(U, "U");
	displaySet(A, "A");
	displaySet(B, "B");
	
	// universal set
	for (int i = 0; i < N_BITS; i++) {
		insert(&U, i);
	}
	
	// set A
	insert(&A, 1);
	insert(&A, 4);
	insert(&A, 0);
	insert(&A, 7);
	
	// set B
	insert(&B, 5);
	insert(&B, 4);
	insert(&B, 3);
	insert(&B, 2);
	insert(&B, 1);
	
	// display sets with inserted values and stuff
	// edit set to include string that's the name of the set
	displaySet(U, "U");
	displaySet(A, "A");
	displaySet(B, "B");
	
	
	// is member of U
	if (member(U, 2)) {
		printf("%d is member of U\n", 2);
	} else {
		printf("%d is not a member of U\n", 2);
	}
	
	// is member of A
	if (member(A, 2)) {
		printf("%d is member of A\n", 2);
	} else {
		printf("%d is not a member of A\n", 2);
	}
	
	// is member of B
	if (member(B, 2)) {
		printf("%d is member of B\n", 2);
	} else {
		printf("%d is not a member of B\n", 2);
	}
	
	SET *C, *D, *E;
	C = (SET*)malloc(sizeof(SET));
	D = (SET*)malloc(sizeof(SET));
	E = (SET*)malloc(sizeof(SET));
	
	initSet(C);
	initSet(D);
	initSet(E);
	
	
	C = unionSet(A, B, "A", "B");
	D = intersection(A, B, "A", "B");
	E = difference(U, A, "U", "A");
	
	deleteElem(&B, 1);
	
	// delete everything from a, and delete an element that doesn't exist from a to make sure
	deleteElem(&A, 1);
	deleteElem(&A, 4);
	deleteElem(&A, 0);
	deleteElem(&A, 7);
	
	// delete element that doesn't exist
	deleteElem(&A, 3);
	
	displaySet(A, "A");
	displaySet(B, "B");
	
	
    return 0;
}

void initSet(SET *A) {
	*A = 0;
}

void displaySet(SET A, char name[]) {
	// i wanted to do left shift, but let's do right shift instead
	SET mask = 1;
	int i = 0;
	printf("%s = {", name);
	for (i, mask; mask > 0; mask = mask << 1, i++) {
		// CASTING
		if ((int) (A & mask) != 0) {
			printf("%d, ", i);
		}
	}
	printf("}\n");
}

void displayOperation(SET A, char set1Name[], char set2Name[2], char operation) {
	SET mask = 1;
	int i = 0;
	printf("%s %c %s = {", set1Name, operation, set2Name);
	for (i, mask; mask > 0; mask = mask << 1, i++) {
		// CASTING
		if ((int) (A & mask) != 0) {
			printf("%d, ", i);
		}
	}
	printf("}\n");
}

void insert(SET *A, int elem) {
	SET mask = 1 << elem;
	*A = (*A) | (char) mask;
}

bool member(SET A, int elem) {
	// displaySet(A);
	SET mask = 1 << elem;
	return ((int) (A & mask) == 0) ? false : true;
} 

void deleteElem(SET *A, int elem) {
	// guard clause lol
	if (member(*A, elem) != true) return;
	SET mask = 1 << elem;
	*A = (*A) ^ mask;
}

SET *unionSet(SET A, SET B, char set1Name[], char set2Name[]) {
	SET *C = (SET*)malloc(sizeof(SET));
	*C = A | B;
	displayOperation(*C, set1Name, set2Name, 'u');
	return C;
}
SET *intersection(SET A, SET B, char set1Name[], char set2Name[]) {
	SET *C = (SET*)malloc(sizeof(SET));
	*C = A & B;
	displayOperation(*C, set1Name, set2Name, 'n');
	return C;
}

SET *difference(SET A, SET B, char set1Name[], char set2Name[]) {
	// what's difference again??
	// the elements in a, that are not in b
	// remember the venn diagram
	// 
	SET *C = (SET*)malloc(sizeof(SET));
	SET complement = ~A;
	*C = A ^ B;
	displayOperation(*C, set1Name, set2Name, '-');
	return C;
}


