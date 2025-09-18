#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// to test
// #include "arraylist.h"
// #include "cursorBased.h" 
#include "linkedList.h"

int countElements(List list) {
    #ifdef ARRAYLIST
        // ArrayList has a count field - easy!
        return list.count;
    #elif defined(CURSORBASED)
        // For cursor-based, traverse the list counting nodes
        int count = 0;
        int current = list.list; // start from the list head
        while (current != -1) {
            count++;
            current = list.Elem[current].link;
        }
        return count;
    #elif defined(LINKEDLIST)
        // For linked list, traverse counting nodes
        // List is typedef'd as Node*, so we can traverse directly
        int count = 0;
        Node *current = list;
        while (current != NULL) {
            count++;
            current = current->link;
        }
        return count;
    #else
        // Fallback
        return isEmpty(list) ? 0 : 1;
    #endif
}

studtype inputStudent() {
    studtype student;
    
    printf("Enter first name: ");
    scanf("%s", student.name.firstName);
    
    printf("Enter last name: ");
    scanf("%s", student.name.lastName);
    
    printf("Enter middle initial: ");
    scanf(" %c", &student.name.MI);
    
    printf("Enter year: ");
    scanf("%d", &student.year);
    
    printf("Enter ID: ");
    scanf("%s", student.ID);
    
    printf("Enter course: ");
    scanf("%s", student.course);
    
    return student;
}

void populate(List *list, int numStudents) {
    // Sample student data for testing
    studtype students[] = {
        {{"Alice", "Johnson", 'M'}, 2021, "20211001", "BSCS"},
        {{"Bob", "Smith", 'A'}, 2022, "20221002", "BSIT"},
        {{"Charlie", "Brown", 'K'}, 2020, "20201003", "BSCE"},
        {{"Diana", "Wilson", 'L'}, 2023, "20231004", "BSEE"},
        {{"Eve", "Davis", 'R'}, 2021, "20211005", "BSCS"},
        {{"Frank", "Miller", 'T'}, 2022, "20221006", "BSIT"},
        {{"Grace", "Taylor", 'S'}, 2020, "20201007", "BSCE"},
        {{"Henry", "Anderson", 'P'}, 2023, "20231008", "BSEE"},
        {{"Ivy", "Thomas", 'Q'}, 2021, "20211009", "BSCS"},
        {{"Jack", "Jackson", 'W'}, 2022, "20221010", "BSIT"}
    };
    
    int maxStudents = sizeof(students) / sizeof(students[0]);
    int studentsToAdd = (numStudents > maxStudents) ? maxStudents : numStudents;
    
    printf("Populating list with %d students...\n", studentsToAdd);
    
    for (int i = 0; i < studentsToAdd && !isFull(*list); i++) {
        // Use different insertion methods for variety
        if (i % 3 == 0) {
            // Insert at beginning
            insertFirst(list, students[i]);
            printf("%d. Inserted %s %s at FIRST\n", i+1, 
                   students[i].name.firstName, students[i].name.lastName);
        } 
        else if (i % 3 == 1) {
            // Insert at end
            insertLast(list, students[i]);
            printf("%d. Inserted %s %s at LAST\n", i+1, 
                   students[i].name.firstName, students[i].name.lastName);
        } 
        else {
            // Insert at middle position
            #ifdef ARRAYLIST
                int middlePos = (isEmpty(*list)) ? 0 : (countElements(*list) / 2);
            #elif defined(CURSORBASED)
                int middlePos = (isEmpty(*list)) ? 0 : (countElements(*list) / 2);
            #elif defined(LINKEDLIST)
                int currentSize = countElements(*list);
                int middlePos = currentSize / 2;  // This ensures valid position (0 to currentSize)
            #else
                int middlePos = 0;
            #endif
            insertPos(list, students[i], middlePos);
            printf("%d. Inserted %s %s at POSITION %d\n", i+1, 
                   students[i].name.firstName, students[i].name.lastName, middlePos);
        }
    }
    
    if (isFull(*list)) {
        printf("List is now FULL!\n");
    }
    printf("Population complete! Added %d students.\n", studentsToAdd);
}

void deleteRandom(List *list, int numToDelete) {
    int currentCount = countElements(*list);
    
    if (currentCount == 0) {
        printf("List is already empty! Nothing to delete.\n");
        return;
    }
    
    // If numToDelete >= MAX or >= currentCount, delete all
    if (numToDelete >= MAX || numToDelete >= currentCount) {
        printf("Deleting ALL %d elements...\n", currentCount);
        numToDelete = currentCount;
    } else {
        printf("Deleting %d random elements...\n", numToDelete);
    }
    
    // Seed random number generator with current time
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < numToDelete && !isEmpty(*list); i++) {
        currentCount = countElements(*list);
        if (currentCount == 0) break;
        
        // Pick random deletion method
        int deleteMethod = rand() % 3;
        
        if (deleteMethod == 0) {
            // Delete first
            printf("%d. Deleting FIRST element\n", i+1);
            deleteFirst(list);
        } 
        else if (deleteMethod == 1 && currentCount > 1) {
            // Delete last (only if more than 1 element)
            printf("%d. Deleting LAST element\n", i+1);
            deleteLast(list);
        } 
        else {
            // Delete at random position
            int randomPos = rand() % currentCount;
            printf("%d. Deleting element at POSITION %d\n", i+1, randomPos);
            deletePos(list, randomPos);
        }
    }
    
    if (isEmpty(*list)) {
        printf("List is now EMPTY!\n");
    }
    printf("Random deletion complete! Remaining elements: %d\n", countElements(*list));
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
    printf("10. Populate List\n");
    printf("11. Delete Random Elements\n");  // New chaos option!
    printf("0. Exit\n");
    printf("Choice: ");
}

int main() {
    List list;
    // LinkedList list;
    // VirtualHeap list;
    initList(&list);
    int choice = -1;
    
    printf("=== ADT List Management System ===\n");
    printf("Current implementation: ");
    #ifdef ARRAYLIST
        printf("ArrayList\n");
    #elif defined(CURSORBASED)
        printf("Cursor-Based List\n");
    #elif defined(LINKEDLIST)
        printf("Linked List\n");
    #else
        printf("Unknown\n");
    #endif
    
    while (choice != 0) {
        showMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                printf("\n--- Insert First ---\n");
                if (isFull(list)) {
                    printf("List is full! Cannot insert.\n");
                } else {
                    studtype student = inputStudent();
                    insertFirst(&list, student);
                    printf("Student inserted at the beginning successfully!\n");
                }
                break;
            }
            
            case 2: {
                printf("\n--- Insert Last ---\n");
                if (isFull(list)) {
                    printf("List is full! Cannot insert.\n");
                } else {
                    studtype student = inputStudent();
                    insertLast(&list, student);
                    printf("Student inserted at the end successfully!\n");
                }
                break;
            }
            
            case 3: {
                printf("\n--- Insert at Position ---\n");
                if (isFull(list)) {
                    printf("List is full! Cannot insert.\n");
                } else {
                    int position;
                    printf("Enter position (0-based index): ");
                    scanf("%d", &position);
                    
                    studtype student = inputStudent();
                    insertPos(&list, student, position);
                    printf("Student inserted at position %d successfully!\n", position);
                }
                break;
            }
            
            case 4: {
                printf("\n--- Delete First ---\n");
                if (isEmpty(list)) {
                    printf("List is empty! Cannot delete.\n");
                } else {
                    deleteFirst(&list);
                    printf("First student deleted successfully!\n");
                }
                break;
            }
            
            case 5: {
                printf("\n--- Delete Last ---\n");
                if (isEmpty(list)) {
                    printf("List is empty! Cannot delete.\n");
                } else {
                    deleteLast(&list);
                    printf("Last student deleted successfully!\n");
                }
                break;
            }
            
            case 6: {
                printf("\n--- Delete at Position ---\n");
                if (isEmpty(list)) {
                    printf("List is empty! Cannot delete.\n");
                } else {
                    int position;
                    printf("Enter position (0-based index): ");
                    scanf("%d", &position);
                    
                    deletePos(&list, position);
                    printf("Student at position %d deleted successfully!\n", position);
                }
                break;
            }
            
            case 7: {
                printf("\n--- Delete Student by ID ---\n");
                if (isEmpty(list)) {
                    printf("List is empty! Cannot delete.\n");
                } else {
                    char studentID[8];
                    printf("Enter student ID to delete: ");
                    scanf("%s", studentID);
                    
                    if (findElem(&list, studentID)) {
                        deleteStudent(&list, studentID);
                        printf("Student with ID %s deleted successfully!\n", studentID);
                    } else {
                        printf("Student with ID %s not found!\n", studentID);
                    }
                }
                break;
            }
            
            case 8: {
                printf("\n--- Find Student by ID ---\n");
                char studentID[8];
                printf("Enter student ID to find: ");
                scanf("%s", studentID);
                
                if (findElem(&list, studentID)) {
                    printf("Student with ID %s found in the list!\n", studentID);
                } else {
                    printf("Student with ID %s not found in the list!\n", studentID);
                }
                break;
            }
            
            case 9: {
                printf("\n--- Display List ---\n");
                displayList(list);
                break;
            }

            case 10: {
                printf("\n--- Populate List ---\n");
                int numStudents;
                printf("Enter number of students to add (max 10): ");
                scanf("%d", &numStudents);
                
                if (numStudents <= 0) {
                    printf("Invalid number! Must be greater than 0.\n");
                } else {
                    populate(&list, numStudents);
                }
                break;
            }

            case 11: {
                printf("\n--- Delete Random Elements ---\n");
                if (isEmpty(list)) {
                    printf("List is empty! Nothing to delete.\n");
                } else {
                    int numToDelete;
                    int currentCount = countElements(list);
                    printf("Current list size: %d\n", currentCount);
                    printf("Enter number of elements to delete (>= %d to delete all): ", currentCount);
                    scanf("%d", &numToDelete);
                    
                    if (numToDelete <= 0) {
                        printf("Invalid number! Must be greater than 0.\n");
                    } else {
                        deleteRandom(&list, numToDelete);
                    }
                }
                break;
            }
            
            case 0: {
                printf("\nExiting program. Goodbye!\n");
                break;
            }
            
            default: {
                printf("\nInvalid choice! Please select a valid option (0-9).\n");
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