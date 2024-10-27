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

#define ZERO_DIVISION_ERROR "ERROR: Cannot divide by 0!\n"
#define STACK_OVERFLOW_ERROR "ERROR: Stack overflow! Reseting the stack...\n"
#define STACK_UNDERFLOW_ERROR "ERROR: Stack underflow! Reseting the stack...\n"