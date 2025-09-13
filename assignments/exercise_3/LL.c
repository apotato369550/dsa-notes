#include <stdio.h>
#include <string.h>

#define ARR_LENGTH 100

// Array Implementation of List
typedef struct {
    char FN[24], MI, LN[16];
} nametype;

typedef struct {
    char ID[9];
    nametype name;
    char course[8];
    int yrLevel;
} studtype;

typedef struct {
    studtype studs[ARR_LENGTH];
    int count;
} ArrayList;

// 1) insertFirst() - Insert element at first position
void insertFirst(ArrayList *list, studtype newStud) {
    int i;
    // Butterfly: shift all elements right, condition checks bounds and moves data
    for (i = list->count; i > 0 && (list->studs[i] = list->studs[i-1], 1); i--);
    list->studs[0] = newStud;
    (list->count < ARR_LENGTH) ? list->count++ : list->count;
}

// 2) insertLast() - Insert element at last position
void insertLast(ArrayList *list, studtype newStud) {
    // Butterfly: condition checks capacity, increment updates count and assigns
    for (; list->count < ARR_LENGTH && (list->studs[list->count] = newStud, list->count++, 0););
}

// 3) insertLastUnique() - Insert at last if ID doesn't exist
void insertLastUnique(ArrayList *list, studtype newStud) {
    int i;
    // Butterfly: search for existing ID, condition stops when found or end reached
    for (i = 0; i < list->count && strcmp(list->studs[i].ID, newStud.ID) != 0; i++);
    // If not found and space available, insert at last
    (i == list->count && list->count < ARR_LENGTH) ? 
        (list->studs[list->count] = newStud, list->count++) : 0;
}

// 4) insertAtPosition() - Insert at given valid position
void insertAtPosition(ArrayList *list, studtype newStud, int pos) {
    int i;
    // Check if position is valid
    if (pos >= 0 && pos <= list->count && list->count < ARR_LENGTH) {
        // Butterfly: shift elements right from end to position
        for (i = list->count; i > pos && (list->studs[i] = list->studs[i-1], 1); i--);
        list->studs[pos] = newStud;
        list->count++;
    }
}

// 5) deleteElem() - Delete element with given ID, return deleted element
studtype deleteElem(ArrayList *list, char targetID[]) {
    int i, j;
    studtype dummy = {"XXXXX", {"XXXXX", 'X', "XXXXX"}, "XXXXX", 0};
    
    // Butterfly: find element with matching ID
    for (i = 0; i < list->count && strcmp(list->studs[i].ID, targetID) != 0; i++);
    
    // If found, save element and shift left, else return dummy
    if (i < list->count) {
        studtype deleted = list->studs[i];
        // Butterfly: shift all elements left from found position
        for (j = i; j < list->count - 1 && (list->studs[j] = list->studs[j+1], 1); j++);
        list->count--;
        return deleted;
    }
    return dummy;
}

// 6) separateCourse() - Remove all elements with given course to new list
ArrayList separateCourse(ArrayList *list, char targetCourse[]) {
    ArrayList newList = {{}, 0};
    int i, j;
    
    // Butterfly: traverse original list, extract matching courses
    for (i = 0, j = 0; i < list->count; ) {
        if (strcmp(list->studs[i].course, targetCourse) == 0) {
            // Add to new list if space available
            (newList.count < ARR_LENGTH) ? 
                (newList.studs[newList.count] = list->studs[i], newList.count++) : 0;
            
            // Butterfly: shift left in original list to remove element
            int k;
            for (k = i; k < list->count - 1 && (list->studs[k] = list->studs[k+1], 1); k++);
            list->count--;
        } else {
            i++; // Only increment if we didn't remove an element
        }
    }
    
    return newList;
}