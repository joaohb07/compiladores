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
#include <constants.h>
#include <stdbool.h>
/* Acumulador*/
extern double acc;
/* Pilha*/
extern double stack[STACKSIZE];
/*ponteiro do topo da pilha*/
extern int sp;
/*Flag de erro*/
extern bool hasError;
/*Mensagem de erro*/
extern char* errorMsg;   

void push(double val);
double pop();
void print_acc();
double calc(char signal, double acc, double stackValue);
