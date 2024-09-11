#include <stdio.h>
#define MAXIDLEN 32;
enum
{
    ID = 1024,
    DEC,
    OCT,
    HEX,
};



extern int linenum;
extern int gettoken(FILE *source);  
