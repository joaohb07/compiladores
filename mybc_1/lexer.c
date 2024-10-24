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
#include <string.h>
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

// NUM = [0-9]|([0-9])"."(([0-9])|"e"("+"|"-")[0-9])[0-9]|([0-9])"."(([0-9])|"e"("+"|"-")[0-9])
int isNUM(FILE *tape)
{
    lexeme[0] = getc(tape);

    if (isdigit(lexeme[0]))
    {
        ungetc(lexeme[0], tape);

        float lexval;

        fscanf(tape, "%f", &lexval);

        sprintf(lexeme, "%f", lexval);

        return NUM;
    }
    ungetc(lexeme[0], tape);
    lexeme[0] = '\0';
    return 0;
}

int isQUIT(FILE *tape)
{
    int i = 0;

    // Lê até o tamanho máximo da palavra "quit"
    while (i < 4)
    {
        lexeme[i] = getc(tape);
        if (lexeme[i] == EOF)
        {
            return 0; // Fim de arquivo ou não formou a palavra
        }
        i++;
    }

    // Adiciona o terminador de string
    lexeme[i] = '\0';

    // Verifica se a palavra é "quit" ou "QUIT"
    if (strcmp(lexeme, "quit") == 0 || strcmp(lexeme, "QUIT") == 0)
    {
        return QUIT; // Retorna um código específico para QUIT
    }

    // Se não for "quit", retorna os caracteres para a fita
    for (int j = i - 1; j >= 0; j--)
    {
        ungetc(lexeme[j], tape);
    }
    return 0; // Não é um comando QUIT
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
    // if ((token = isQUIT(source)))
    // {
    //     return token;
    // }
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
