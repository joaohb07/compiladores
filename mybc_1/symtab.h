#include <lexer.h>

int lookup(char *varname);
void store(char *varname, double value);

/* TO DO: implementar recall, que retorna o valor de uma variavel, se a variavel não existir retorne 0 */
double recall(char *varname);

/* memória da calculadora */
extern double vmem[];
/* tabela de simbolos */
extern char symtab[SYMTABSIZE][MAXIDLEN + 1];
/* symtab_next_entry */
extern int symtab_next_entry;
