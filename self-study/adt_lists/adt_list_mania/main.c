#include <stdio.h>
#include <string.h>

// to test
#include "arraylist.h"
// #include "cursorBased.h" 
// #include "linkedList.h"

void displayList(ArrayList *L) {
    if (isEmpty(*L)) {
        printf("List is empty.\n");
        return;
    }
    
    printf("\nCurrent List:\n");
    for (int i = 0; i < L->count; i++) {
        printf("%d. %s %c %s - ID: %s, Year: %d, Course: %s\n", 
               i+1, L->Elem[i].name.firstName, L->Elem[i].name.MI, 
               L->Elem[i].name.lastName, L->Elem[i].ID, 
               L->Elem[i].year, L->Elem[i].course);
    }
    printf("\n");
}

studtype inputStudent() {
    studtype student;
    
    printf("Enter first name: ");
    scanf("%23s", student.name.firstName);
    
    printf("Enter last name: ");
    scanf("%15s", student.name.lastName);
    
    printf("Enter middle initial: ");
    scanf(" %c", &student.name.MI);
    
    printf("Enter year: ");
    scanf("%d", &student.year);
    
    printf("Enter ID: ");
    scanf("%7s", student.ID);
    
    printf("Enter course: ");
    scanf("%7s", student.course);
    
    return student;
}

void showMenu() {
    printf("\n=== ADT List Operations ===\n");
    printf("1. Insert First\n");
    printf("2. Insert Last\n");
    printf("3. Insert at Position\n");
    printf("4. Delete First\n");
    printf("5. Delete Last\n");
    printf("6. Delete at Position\n");
    printf("7. Delete Student by ID\n");
    printf("8. Find Student by ID\n");
    printf("9. Display List\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main() {
    ArrayList list;
    initList(&list);
    
    int choice;
    studtype student;
    int pos;
    char id[8];
    
    do {
        showMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if (isFull(list)) {
                    printf("List is full!\n");
                } else {
                    printf("\nEnter student data:\n");
                    student = inputStudent();
                    insertFirst(&list, student);
                    printf("Student inserted at first position.\n");
                }
                break;
                
            case 2:
                if (isFull(list)) {
                    printf("List is full!\n");
                } else {
                    printf("\nEnter student data:\n");
                    student = inputStudent();
                    insertLast(&list, student);
                    printf("Student inserted at last position.\n");
                }
                break;
                
            case 3:
                if (isFull(list)) {
                    printf("List is full!\n");
                } else {
                    printf("Enter position (0-%d): ", list.count);
                    scanf("%d", &pos);
                    if (pos >= 0 && pos <= list.count) {
                        printf("\nEnter student data:\n");
                        student = inputStudent();
                        insertPos(&list, student, pos);
                        printf("Student inserted at position %d.\n", pos);
                    } else {
                        printf("Invalid position!\n");
                    }
                }
                break;
                
            case 4:
                if (isEmpty(list)) {
                    printf("List is empty!\n");
                } else {
                    deleteFirst(&list);
                    printf("First student deleted.\n");
                }
                break;
                
            case 5:
                if (isEmpty(list)) {
                    printf("List is empty!\n");
                } else {
                    deleteLast(&list);
                    printf("Last student deleted.\n");
                }
                break;
                
            case 6:
                if (isEmpty(list)) {
                    printf("List is empty!\n");
                } else {
                    printf("Enter position (0-%d): ", list.count-1);
                    scanf("%d", &pos);
                    if (pos >= 0 && pos < list.count) {
                        deletePos(&list, pos);
                        printf("Student at position %d deleted.\n", pos);
                    } else {
                        printf("Invalid position!\n");
                    }
                }
                break;
                
            case 7:
                if (isEmpty(list)) {
                    printf("List is empty!\n");
                } else {
                    printf("Enter student ID to delete: ");
                    scanf("%7s", id);
                    deleteStudent(&list, id);
                    printf("Attempted to delete student with ID: %s\n", id);
                }
                break;
                
            case 8:
                if (isEmpty(list)) {
                    printf("List is empty!\n");
                } else {
                    printf("Enter student ID to find: ");
                    scanf("%7s", id);
                    if (findElem(&list, id)) {
                        printf("Student with ID %s found!\n", id);
                    } else {
                        printf("Student with ID %s not found.\n", id);
                    }
                }
                break;
                
            case 9:
                displayList(&list);
                break;
                
            case 0:
                printf("Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
        
    } while (choice != 0);
    
    return 0;
}