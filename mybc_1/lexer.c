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

char lexeme[MAXIDLEN + 1];  // Armazena o valor numérico lido como string

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

int isNUM(FILE *tape)
{
    int i = 0;
    char c;

    // Primeira leitura de dígitos ou ponto
    c = getc(tape);
    if (isdigit(c) || c == '.')
    {
        lexeme[i++] = c;

        // Continua lendo dígitos
        while ((c = getc(tape)) && (isdigit(c) || c == '.'))
        {
            lexeme[i++] = c;
        }

        // Verifica se encontrou notação científica
        if (c == 'e' || c == 'E')
        {
            lexeme[i++] = c;
            c = getc(tape);

            // Pode ser seguido de '+' ou '-' no expoente
            if (c == '+' || c == '-')
            {
                lexeme[i++] = c;
                c = getc(tape);
            }

            // Continua lendo os dígitos do expoente
            while (isdigit(c))
            {
                lexeme[i++] = c;
                c = getc(tape);
            }
        }

        ungetc(c, tape); // Devolve o último caractere não numérico
        lexeme[i] = '\0'; // Finaliza a string em lexeme
        return NUM;
    }

    // Se não for um número válido, devolve o caractere lido e retorna 0
    ungetc(c, tape);
    lexeme[0] = '\0';
    return 0;
}

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
