#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <calculator.h>


double acc;              // Acumulador
double stack[STACKSIZE]; // Pilha
int sp = -1;             // Inicializado com -1, pois a pilha está vazia

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