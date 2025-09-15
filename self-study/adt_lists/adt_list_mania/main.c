#include <stdio.h>
#include <string.h>

// to test
#include "arraylist.h"
// #include "cursorBased.h" 
// #include "linkedList.h"
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
    // LinkedList list;
    // VirtualHeap list;
    initList(&list);
    
    
    // write menu and interface (later)
    
    return 0;
}