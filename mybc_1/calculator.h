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
#include<constants.h>
extern double acc;              // Acumulador
extern double stack[STACKSIZE]; // Pilha
extern int sp;                  // Índice do topo da pilha

void push(double val);
double pop();
void print_acc();
double calc(char signal, double acc, double stackValue);
