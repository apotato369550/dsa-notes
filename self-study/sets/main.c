#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Choose implementation: uncomment one
#define BIT_VECTOR
// #define COMPUTER_WORD

#ifdef BIT_VECTOR
#include "bit_vector.h"
#define SET_TYPE SET
#define INIT_SET(A) initSet(A)
#define DISPLAY_SET(A, name) displaySet(A, name)
#define INSERT(A, elem) insert(A, elem)
#define IS_MEMBER(A, elem) isMember(A, elem)
#define DELETE_ELEM(A, elem) deleteElem(A, elem)
#define UNION(A, B) unionSet(A, B)
#define INTERSECTION(A, B) intersectionSet(A, B)
#define DIFFERENCE(A, B) differenceSet(A, B)
#define FREE_SET(C) free(C)
#define MAX_ELEM N_ELEM
#elif defined(COMPUTER_WORD)
#include "computer_word.h"
#define SET_TYPE SET
#define INIT_SET(A) initSet(&A)
#define DISPLAY_SET(A, name) displaySet(A, name)
#define INSERT(A, elem) insert(&A, elem)
#define IS_MEMBER(A, elem) isMember(A, elem)
#define DELETE_ELEM(A, elem) deleteElem(&A, elem)
#define UNION(A, B) ({ SET *temp = (SET*)malloc(sizeof(SET)); *temp = unionSet(A, B); temp; })
#define INTERSECTION(A, B) ({ SET *temp = (SET*)malloc(sizeof(SET)); *temp = intersectionSet(A, B); temp; })
#define DIFFERENCE(A, B) ({ SET *temp = (SET*)malloc(sizeof(SET)); *temp = differenceSet(A, B); temp; })
#define FREE_SET(C) free(C)
#define MAX_ELEM N_BITS
#endif

void populateRandom(SET_TYPE *set, int numElements) {
    srand((unsigned int)time(NULL));
    printf("Populating with %d random elements...\n", numElements);
    for (int i = 0; i < numElements; i++) {
        int elem = rand() % MAX_ELEM;
        INSERT(*set, elem);
        printf("Inserted %d\n", elem);
    }
}

void deleteRandom(SET_TYPE *set, int numToDelete) {
    int deleted = 0;
    srand((unsigned int)time(NULL));
    printf("Deleting %d random elements...\n", numToDelete);
    for (int i = 0; i < numToDelete; i++) {
        int attempts = 0;
        while (attempts < MAX_ELEM * 2) {  // reasonable attempts
            int elem = rand() % MAX_ELEM;
            if (IS_MEMBER(*set, elem)) {
                DELETE_ELEM(*set, elem);
                printf("Deleted %d\n", elem);
                deleted++;
                break;
            }
            attempts++;
        }
        if (attempts >= MAX_ELEM * 2) {
            printf("No more elements to delete.\n");
            break;
        }
    }
    printf("Deleted %d elements.\n", deleted);
}

void showMenu() {
    printf("\n=== Set Operations Driver ===\n");
    printf("Current implementation: ");
#ifdef BIT_VECTOR
    printf("Bit Vector\n");
#elif defined(COMPUTER_WORD)
    printf("Computer Word\n");
#endif
    printf("1. Initialize sets A and B\n");
    printf("2. Insert element to set A\n");
    printf("3. Insert element to set B\n");
    printf("4. Delete element from set A\n");
    printf("5. Delete element from set B\n");
    printf("6. Display sets A and B\n");
    printf("7. Union (A ∪ B)\n");
    printf("8. Intersection (A ∩ B)\n");
    printf("9. Difference (A - B)\n");
    printf("10. Populate set A randomly\n");
    printf("11. Populate set B randomly\n");
    printf("12. Delete random elements from A\n");
    printf("13. Delete random elements from B\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main() {
    SET_TYPE A, B;
    int choice = -1;

    printf("=== Set ADT Driver Program ===\n");

    while (choice != 0) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("\n--- Initialize Sets ---\n");
                INIT_SET(A);
                INIT_SET(B);
                printf("Sets A and B initialized.\n");
                break;
            }

            case 2: {
                printf("\n--- Insert to Set A ---\n");
                int elem;
                printf("Enter element (0-%d): ", MAX_ELEM - 1);
                scanf("%d", &elem);
                if (elem >= 0 && elem < MAX_ELEM) {
                    INSERT(A, elem);
                    printf("Inserted %d into A.\n", elem);
                } else {
                    printf("Invalid element.\n");
                }
                break;
            }

            case 3: {
                printf("\n--- Insert to Set B ---\n");
                int elem;
                printf("Enter element (0-%d): ", MAX_ELEM - 1);
                scanf("%d", &elem);
                if (elem >= 0 && elem < MAX_ELEM) {
                    INSERT(B, elem);
                    printf("Inserted %d into B.\n", elem);
                } else {
                    printf("Invalid element.\n");
                }
                break;
            }

            case 4: {
                printf("\n--- Delete from Set A ---\n");
                int elem;
                printf("Enter element (0-%d): ", MAX_ELEM - 1);
                scanf("%d", &elem);
                if (elem >= 0 && elem < MAX_ELEM) {
                    DELETE_ELEM(A, elem);
                    printf("Deleted %d from A.\n", elem);
                } else {
                    printf("Invalid element.\n");
                }
                break;
            }

            case 5: {
                printf("\n--- Delete from Set B ---\n");
                int elem;
                printf("Enter element (0-%d): ", MAX_ELEM - 1);
                scanf("%d", &elem);
                if (elem >= 0 && elem < MAX_ELEM) {
                    DELETE_ELEM(B, elem);
                    printf("Deleted %d from B.\n", elem);
                } else {
                    printf("Invalid element.\n");
                }
                break;
            }

            case 6: {
                printf("\n--- Display Sets ---\n");
                DISPLAY_SET(A, "A");
                printf("\n");
                DISPLAY_SET(B, "B");
                printf("\n");
                break;
            }

            case 7: {
                printf("\n--- Union (A ∪ B) ---\n");
                SET_TYPE *C = UNION(A, B);
                DISPLAY_SET(*C, "A ∪ B");
                printf("\n");
                FREE_SET(C);
                break;
            }

            case 8: {
                printf("\n--- Intersection (A ∩ B) ---\n");
                SET_TYPE *C = INTERSECTION(A, B);
                DISPLAY_SET(*C, "A ∩ B");
                printf("\n");
                FREE_SET(C);
                break;
            }

            case 9: {
                printf("\n--- Difference (A - B) ---\n");
                SET_TYPE *C = DIFFERENCE(A, B);
                DISPLAY_SET(*C, "A - B");
                printf("\n");
                FREE_SET(C);
                break;
            }

            case 10: {
                printf("\n--- Populate Set A Randomly ---\n");
                int num;
                printf("Enter number of elements to add: ");
                scanf("%d", &num);
                if (num > 0) {
                    populateRandom(&A, num);
                } else {
                    printf("Invalid number.\n");
                }
                break;
            }

            case 11: {
                printf("\n--- Populate Set B Randomly ---\n");
                int num;
                printf("Enter number of elements to add: ");
                scanf("%d", &num);
                if (num > 0) {
                    populateRandom(&B, num);
                } else {
                    printf("Invalid number.\n");
                }
                break;
            }

            case 12: {
                printf("\n--- Delete Random from A ---\n");
                int num;
                printf("Enter number of elements to delete: ");
                scanf("%d", &num);
                if (num > 0) {
                    deleteRandom(&A, num);
                } else {
                    printf("Invalid number.\n");
                }
                break;
            }

            case 13: {
                printf("\n--- Delete Random from B ---\n");
                int num;
                printf("Enter number of elements to delete: ");
                scanf("%d", &num);
                if (num > 0) {
                    deleteRandom(&B, num);
                } else {
                    printf("Invalid number.\n");
                }
                break;
            }

            case 0: {
                printf("\nExiting program. Goodbye!\n");
                break;
            }

            default: {
                printf("\nInvalid choice! Please select a valid option.\n");
                break;
            }
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // consume newline
            getchar(); // wait for Enter
        }
    }

    return 0;
}