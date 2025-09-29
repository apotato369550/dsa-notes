#ifndef STUDTYPE
#define STUDTYPE

typedef struct {
    char firstName[24];
    char lastName[16];
    char MI;
} nametype;

typedef struct {
    nametype name;
    int year;
    char ID[8];
    char course[8];
} studtype;

#endif