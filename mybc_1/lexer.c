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

// NUM = [0-9]*|([0-9]*)"."(([0-9]*)|"e"("+"|"-")[0-9]*)[0-9]*|([0-9]*)"."(([0-9]*)|"e"("+"|"-")[0-9])
int isNUM(FILE *tape)
{
    int i = 0;
    char c;

    c = getc(tape);
    if (isdigit(c) || c == '.')
    {
        lexeme[i++] = c;

        while ((c = getc(tape)) && (isdigit(c) || c == '.'))
        {
            lexeme[i++] = c;
        }

        if (c == 'e' || c == 'E')
        {
            lexeme[i++] = c;
            c = getc(tape);

            if (c == '+' || c == '-')
            {
                lexeme[i++] = c;
                c = getc(tape);
            }

            while (isdigit(c))
            {
                lexeme[i++] = c;
                c = getc(tape);
            }
        }
        ungetc(c, tape);
        lexeme[i] = '\0';
        return NUM;
    }
    ungetc(c, tape);
    lexeme[0] = '\0';
    return 0;
}

/*
    skipspaces ignora os espaços em branco e troca fim de linha por ; para delimitar expressões
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

/*
    gettoken verifica se o tipo do proximo simbolo a ser processado
*/
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
