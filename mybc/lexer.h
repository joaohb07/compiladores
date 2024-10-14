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
 *  //descrição do lexer.h
 ***************************************************/
#include <stdio.h>
#define MAXIDLEN 32
enum
{
    ID = 1024,
    DEC,
    OCT,
    HEX,
};


extern char lexeme[];
extern int linenum;
extern int gettoken(FILE *source);  
