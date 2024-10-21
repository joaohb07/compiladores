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

FILE *source;

int main()
{
   source = stdin;
   lookahead = gettoken(source);
   int i = 0;
   while (lookahead != EOF)
   {
      E();
      print_acc();
   }

   return 0;
}
