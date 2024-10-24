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
#include <calculator.h>
#include <parser.h>
#include <lexer.h>
#include <stdbool.h>

FILE *source;

int main()
{
   source = stdin;
   lookahead = gettoken(source);
   int i = 0;
   while (lookahead != EOF)
   {
      E();
      if ((lookahead == ';' || lookahead == '\n') && hasError == false) {
         print_acc();
      } else if (hasError) {
         printf("%s", errorMsg);
         hasError = false;
      }
   }

   return 0;
}
