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
#include <parser.h>
#include <lexer.h>

FILE *source;

int main()
{
   source = stdin;
   lookahead = gettoken(source);
   while (1)
   {
      E();
   }

   return 0;
}
