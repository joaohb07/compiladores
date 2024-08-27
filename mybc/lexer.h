#include <stdio.h>

enum
{
    ID = 1024,
    DEC,
    OCT,
    HEX,
};

extern int linenum;
extern int gettoken(FILE *source);
