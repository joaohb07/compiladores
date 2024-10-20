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
#include <math.h>
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
      if (acc == floor(acc))
      {
         printf("%.0f\n", acc);
      }
      else
      {
         printf("%f\n", acc);
      }
   }

   return 0;
}
