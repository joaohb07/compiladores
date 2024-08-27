#include <stdio.h>
#include <parser.h>
#include <lexer.h>

FILE *source;

int main()
{
   source = stdin;
   lookahead = gettoken(source);
   E();
   printf("%d lines read\n", linenum);
   return 0;
}