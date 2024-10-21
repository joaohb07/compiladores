// stack.c
#include <stdio.h>
#include <stdlib.h>
#include <stack.h>

double stack[STACKSIZE]; // Pilha
int sp = -1;             // Inicializado com -1, pois a pilha está vazia

double pop() {
    if (sp == -1) { // Verifica se a pilha está vazia
        fprintf(stderr, "Error: Empty stack!.\n");
        exit(EXIT_FAILURE);
    }
    double result = stack[sp];
    sp--;
    return result; // Retorna o valor e decrementa sp
}

void push(double val) {
    if (sp == STACKSIZE - 1) { // Verifica se a pilha está cheia
        fprintf(stderr, "Error: Full stack! %f.\n", val);
        exit(EXIT_FAILURE);
    }
    ++sp;
    stack[sp] = val; // Incrementa sp e armazena o valor
}
