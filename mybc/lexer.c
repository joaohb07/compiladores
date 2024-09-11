#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <lexer.h>

int linenum = 1;

char lexeme[MAXIDLEN + 1];

// ID = [A-Za-z][A-Za-z0-9]*
int isID(FILE *tape)
{
    int i = 0;

    if (isalpha(lexeme[i] = getc(tape)))
    {
        ++i;
        while (isalnum(lexeme[i] = getc(tape)))
            ++i;
        
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;

        return ID;
    }
    ungetc(lexeme[i], tape);
    return 0;
}

// DEC = [1-9][0-9]* | 0
int isDEC(FILE *tape)
{
    int i = 0;

    if (isdigit(lexeme[i] = getc(tape)))
    {
        ++i;
        if (lexeme[i] == '0')
        {
            return DEC;
        }
        while (isdigit(lexeme[i] = getc(tape)))
            ++i;

        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        return DEC;
    }
    ungetc(lexeme[i], tape);
    return 0;
}

// OCT = 0[0-7]+
int isOCT(FILE *tape)
{
    int i = 0;
    lexeme[i] = getc(tape);
    if (lexeme[i] == '0')
    {
        ++i;
        while (lexeme[i] >= '0' && lexeme[i] <= '7'){
            lexeme[i] = getc(tape);
            ++i;
        }
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        return OCT;
    }
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
    return 0;
}

// HEX = 0(x|X)[0-9a-fA-F]+
int isHEX(FILE *tape)
{
    int i = 0;
    lexeme[i] = getc(tape);
    if (lexeme[i] == '0')

    {
        ++i;
        lexeme[i] = getc(tape);
        if (lexeme[i] == 'x' || lexeme[i] == 'X')
        {
            ++i;
            while (isxdigit(lexeme[i] = getc(tape)))
                ++i;
            ungetc(lexeme[i], tape);
            lexeme[i] = 0;
            return HEX;
        }
        ungetc(lexeme[i], tape);
        --i;
    }
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
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
