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
    // bug: made this too small. null terminator would not fit in
    // fix: made it 16 instead
    char ID[16];
    char course[8];
} studtype;

#endif