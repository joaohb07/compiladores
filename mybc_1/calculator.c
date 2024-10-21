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
#include <stdlib.h>
#include <math.h>
#include <calculator.h>

double acc;            
double stack[STACKSIZE];
int sp = -1;            

/*
    pop desempilha
*/
double pop()
{
    if (sp == -1)
    { // Verifica se a pilha está vazia
        fprintf(stderr, "Error: Empty stack!.\n");
        exit(EXIT_FAILURE);
    }
    double result = stack[sp];
    sp--;
    return result; // Retorna o valor e decrementa sp
}

/*
    push empilha
*/
void push(double val)
{
    if (sp == STACKSIZE - 1)
    { // Verifica se a pilha está cheia
        fprintf(stderr, "Error: Full stack! %f.\n", val);
        exit(EXIT_FAILURE);
    }
    ++sp;
    stack[sp] = val; // Incrementa sp e armazena o valor
}
/*
    calc realiza as quatro operações basicas + - * e /
*/
double calc(char signal, double acc, double stackValue)
{
    switch (signal)
    {
    case '+':
        return stackValue + acc;
    case '-':
        return stackValue - acc;
    case '*':
        return stackValue * acc;
    case '/':
        if (acc == 0)
            return 0;
        return stackValue / acc;
    default:
        break;
    }
};


/*
    print_acc imprime o valor do acumulador
*/
void print_acc()
{
    if (acc == floor(acc))
    {
        printf("%.0f\n", acc);
    }
    else
    {
        printf("%f\n", acc);
    }
}