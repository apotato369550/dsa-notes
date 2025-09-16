#include <stdio.h>
#include <string.h>

// to test
#include "studtype.h"
// #include "arraylist.h"
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

int main() {
    
    
    // write menu and interface (later)
    
    return 0;
}