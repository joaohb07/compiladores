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
#include <stdlib.h>

extern FILE *source;
extern void match(int expected);
extern int lookahead;

extern void E(void);
extern void T(void);
extern void F(void);
