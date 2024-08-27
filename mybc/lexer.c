#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <lexer.h>

int linenum = 0;

// ID = [A-Za-z][A-Za-z0-9]*
int isID(FILE *tape)
{

    int head = getc(tape);
    if (isalpha(head))
    {
        while (isalnum(head = getc(tape)))
            ;
        ungetc(head, tape);
        return ID;
    }
    ungetc(head, tape);
    return 0;
}

// DEC = [1-9][0-9]* | 0
int isDEC(FILE *tape)
{
    int head = getc(tape);
    if (isdigit(head))
    {
        if (head == '0')
        {
            return DEC;
        }
        while (isdigit(head = getc(tape)))
            ;
        ungetc(head, tape);
        return DEC;
    }
    ungetc(head, tape);
    return 0;
}

// OCT = 0[0-7]+
int isOCT(FILE *tape)
{
    int head = getc(tape);
    if (head == '0')
    {
        while (head >= '0' && head <= '7')
            head = getc(tape);
        ungetc(head, tape);
        return OCT;
    }
    ungetc(head, tape);

    return 0;
}

// HEX = 0(x|X)[0-9a-fA-F]+
int isHEX(FILE *tape)
{
    int head = getc(tape);
    if (head == '0')
    {
        head = getc(tape);
        if (head == 'x' || head == 'X')
        {
            while (isxdigit(head = getc(tape)))
                ;
            ungetc(head, tape);
            return HEX;
        }
        ungetc(head, tape);
    }
    ungetc(head, tape);
    return 0;
}

void skipspaces(FILE *tape)
{
    int head;
    while (isspace(head = getc(tape)))
    {
        if (head == '\n')
            linenum++;
    };
    ungetc(head, tape);
}

int gettoken(FILE *source)
{
    int token;
    skipspaces(source);
    if ((token = isHEX(source)))
        return token;
    if ((token = isOCT(source)))
        return token;
    if ((token = isDEC(source)))
        return token;
    if ((token = isID(source)))
        return token;
    token = getc(source);
    return token;
}
