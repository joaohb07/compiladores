/***************************************************
 * Compiladores - Noturno - 2024
 * Professor Eraldo Pereira Marinho
 *
 * Mybc
 *
 * Grupo:
 * Cristian Santos de Castro
 * João Henrique Botelho
 * João Pedro Brum Terra
 *
 ***************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <lexer.h>

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
    lexeme[i] = 0;
    return 0;
}

// ASGN = ":="
int isASGN(FILE *tape)
{
    int i = 0;
    lexeme[i] = getc(tape);
    if (lexeme[i] == ':')
    {
        i++;
        lexeme[i] = getc(tape);
        if (lexeme[i] == '=')
        {
            // ungetc(lexeme[i], tape);
            lexeme[i] = 0;
            return ASGN;
        }
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        --i;
    }
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
    return 0;
}

// // DEC = [1-9][0-9]* | 0
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
        return NUM;
    }
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
    return 0;
}

int isNUM(FILE *tape)
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

        // Verifica se o numero é um ponto flutuante
        if (lexeme[i] == '.')
        {
            ++i;
            while (isdigit(lexeme[i] = getc(tape)))
                ++i;

            // |"e"("+"|"-")[0-9]*)
            if (lexeme[i] == 'e')
            {
                ++i;
                lexeme[i] = getc(tape);
                if (lexeme[i] == '+')
                {
                    ++i;
                    while (isdigit(lexeme[i] = getc(tape)))
                        ++i;

                    ungetc(lexeme[i], tape);
                    lexeme[i] = 0;
                    return NUM;
                }
                if (lexeme[i] == '-')
                {
                    ++i;
                    while (isdigit(lexeme[i] = getc(tape)))
                        ++i;

                    ungetc(lexeme[i], tape);
                    lexeme[i] = 0;
                    return NUM;
                }
            }

            ungetc(lexeme[i], tape);
            lexeme[i] = 0;
            return NUM;
        }

        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        return NUM;
    }

    if (lexeme[i] == '.')
    {
        lexeme[i] = '0';
        ++i;
        lexeme[i] = '.';
        ++i;
        while (isdigit(lexeme[i] = getc(tape)))
            ++i;

        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        return NUM;
    }

    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
    return 0;
}

/*

// OCT = 0[0-7]+
int isOCT(FILE *tape)
{
    int i = 0;
    lexeme[i] = getc(tape);
    if (lexeme[i] == '0')
    {
        ++i;
        lexeme[i] = getc(tape);
        while (lexeme[i] >= '0' && lexeme[i] <= '7')
        {
            ++i;
            lexeme[i] = getc(tape);
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
*/
void skipspaces(FILE *tape)
{
    int head;
    while (isspace(head = getc(tape)))
    {
        if (head == '\n')
        {
            ungetc(';', tape);
            return;
        }
    };
    ungetc(head, tape);
}

int gettoken(FILE *source)
{
    int token;
    skipspaces(source);
    if ((token = isID(source)))
    {
        return token;
    }
    if ((token = isNUM(source)))
    {

        return token;
    }
    if ((token = isASGN(source)))
    {

        return token;
    }
    token = getc(source);
    return token;
}
