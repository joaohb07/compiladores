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
#include <parser.h>
#include <lexer.h>

FILE *source;

int main()
{
   source = stdin;
   lookahead = gettoken(source);

   cmd();
   while (lookahead == ';' || lookahead == '\n')
   {
      match(lookahead);
      cmd();
   }
   match(EOF);

   return 0;
}
