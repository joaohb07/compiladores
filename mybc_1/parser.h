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
/* proximo simbolo a ser processado */
extern int lookahead;
extern void match(int expected);
extern void cmd(void);

void E(void);
void T(void);
void F(void);