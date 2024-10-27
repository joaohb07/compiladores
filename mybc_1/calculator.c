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
#include <stdbool.h>
#include <calculator.h>

double acc;
double stack[STACKSIZE];
int sp = -1;
bool hasError = false;
char *errorMsg;

/*
    pop desempilha
*/
double pop()
{
    if (sp == -1)
    {
        errorMsg = STACK_UNDERFLOW_ERROR;
        hasError = true;
        sp = -1;
        return -1;
    }
    double result = stack[sp];
    sp--;
    return result;
}

/*
    push empilha
*/
void push(double val)
{
    if (sp == STACKSIZE - 1)
    {
        errorMsg = STACK_OVERFLOW_ERROR;
        hasError = true;
        sp = -1;
        return;
    }
    ++sp;
    stack[sp] = val;
}

/*
    calc realiza as quatro operações basicas + - * e /
*/
double calc(char op, double a, double b)
{
    switch (op)
    {
    case '+':
        return b + a;
    case '-':
        return b - a;
    case '*':
        return b * a;
    case '/':
        if (a == 0)
        {
            errorMsg = ZERO_DIVISION_ERROR;
            hasError = true;
            break;
        }
        return b / a;
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