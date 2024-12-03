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
#define STACKSIZE 1024
#define MAXIDLEN 32
#define SYMTABSIZE 256

#define ZERO_DIVISION_ERROR     "\033[31mERROR:\033[0m Cannot divide by 0!\n"
#define STACK_OVERFLOW_ERROR    "\033[31mERROR:\033[0m Stack overflow! Reseting the stack...\n"
#define STACK_UNDERFLOW_ERROR   "\033[31mERROR:\033[0m Stack underflow! Reseting the stack...\n"
#define SYNTAX_ERROR            "\033[31mERROR:\033[0m Syntax error.\n"