#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <lexer.h>

int linenum = 1;

// ID = [A-Za-z][A-Za-z0-9]*
int isID(FILE *tape)
{
    int head = getc(tape);
    if (head == EOF)
        return 0;

    if (isalpha(head))
    {
        printf("Starting ID with: %c\n", head);
        while (isalnum(head = getc(tape)))
        {
            if (head == EOF)
                break;
        }
        ungetc(head, tape);
        printf("Found ID token.\n");
        return ID;
    }
    ungetc(head, tape);
    return 0;
}

// DEC = [1-9][0-9]* | 0
int isDEC(FILE *tape)
{
    int head = getc(tape);
    if (head == EOF)
        return 0;

    if (isdigit(head))
    {
        printf("Starting DEC with: %c\n", head);
        if (head == '0')
        {
            printf("Found DEC token: 0\n");
            return DEC;
        }
        while (isdigit(head = getc(tape)))
        {
            if (head == EOF)
                break;
        }
        ungetc(head, tape);
        printf("Found DEC token.\n");
        return DEC;
    }
    ungetc(head, tape);
    return 0;
}

// OCT = 0[0-7]+
int isOCT(FILE *tape)
{
    int head = getc(tape);
    if (head == EOF)
        return 0;

    if (head == '0')
    {
        head = getc(tape);
        if (head == EOF)
        {
            ungetc(head, tape);
            printf("Found OCT token: 0\n");
            return OCT;
        }

        if (head >= '0' && head <= '7')
        {
            printf("Starting OCT with: 0%c\n", head);
            while (head >= '0' && head <= '7')
            {
                head = getc(tape);
                if (head == EOF)
                    break;
            }
            ungetc(head, tape);
            printf("Found OCT token.\n");
            return OCT;
        }
        ungetc(head, tape);
        printf("Single '0', returning DEC token.\n");
        return DEC;
    }
    ungetc(head, tape);
    return 0;
}

// HEX = 0(x|X)[0-9a-fA-F]+
int isHEX(FILE *tape)
{
    int head = getc(tape);
    if (head == EOF)
        return 0;

    if (head == '0')
    {
        head = getc(tape);
        if (head == EOF)
        {
            ungetc(head, tape);
            printf("Found DEC token: 0\n");
            return DEC; // A single '0' should be considered as DEC
        }

        if (head == 'x' || head == 'X')
        {
            printf("Starting HEX with: 0%c\n", head);
            head = getc(tape);
            if (isxdigit(head))
            {
                while (isxdigit(head))
                {
                    head = getc(tape);
                    if (head == EOF)
                        break;
                }
                ungetc(head, tape);
                printf("Found HEX token.\n");
                return HEX;
            }
            else
            {
                ungetc(head, tape);
                printf("Invalid HEX sequence.\n");
                return 0; // Invalid HEX sequence
            }
        }
        ungetc(head, tape);
        //printf("Returning DEC token.\n");
        //return DEC;
    }
    ungetc(head, tape);
    return 0;
}

void skipspaces(FILE *tape)
{
    int head;
    while ((head = getc(tape)) != EOF && isspace(head))
    {
        if (head == '\n')
        {
            linenum++;
            printf("New line encountered, line number: %d\n", linenum);
        }
    }
    ungetc(head, tape);
}

int gettoken(FILE *source)
{
    int token;
    skipspaces(source);

    if ((token = isDEC(source)))
    {
        printf("Token identified as DEC.\n");
        return token;
    }
    if ((token = isHEX(source)))
    {
        printf("Token identified as HEX.\n");
        return token;
    }
    if ((token = isOCT(source)))
    {
        printf("Token identified as OCT.\n");
        return token;
    }
    if ((token = isID(source)))
    {
        printf("Token identified as ID.\n");
        return token;
    }
    token = getc(source);
    printf("Token identified as: %c (ASCII: %d)\n", token, token);
    return token;
}