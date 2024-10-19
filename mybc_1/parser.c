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
 *  //descrição do parser.c
 ***************************************************/
#include <lexer.h>
#include <string.h>
#include <symtab.h>
#include <parser.h>

#define STACKSIZE 1024
double stack[STACKSIZE]; // pilha vai de 0  a STACKSIZE-1
int sp = -1;             // inicializado com - 1, pois a pilha está vazia

// TO DO: decidir onde a logica de pilha deve ficar
double pop()
{
    // TO DO: implementar pop da pilha, lembrar de decrementar sp
}

void push(double val)
{
    // TO DO: implementar push da pilha, lembrar de incrementar sp
}

int lookahead;
double acc; // acumulador

/* TO DO: ATUALIZAR ESTA GRAMATICA ↓
   LL(1) grammar:
 *
 *  E -> ['+'|'-'] T R
 *  T -> F Q
 *  F -> (E) | DEC | ID
 *  R -> +T R | -T R | <>
 *  Q -> *F Q | /F Q | <>
 */

// E -> [oplus] T R
// oplus = '+' || '-'
void E(void)
{
    /*0*/ int oplus = 0, signal = 0; /*0*/
    if (lookahead == '+' || lookahead == '-')
    {
        !(lookahead == '-') || (signal = lookahead);
        match(lookahead);
    }
_T:
    T(); // valor computado aqui é armazenado em acc
    /*1*/
    if (signal)
    {
        printf("\tneg acc");
        signal = 0;
    }
    /*1*/

    /*2*/
    if (oplus)
    {
        switch (oplus)
        {
        case '+':
            printf("\tadd acc, stack[sp]\n");
            break;
        case '-':
            printf("\tsub acc, stack[sp]\n");
            break;
        }
        printf("\tpop acc\n");
        oplus = 0;
    }
    /*2*/

    if (lookahead == '+' || lookahead == '-')
    {
        /*3*/
        oplus = lookahead;
        printf("\tpush acc\n");
        /*3*/
        match(lookahead);
        goto _T;
    }
}

// T -> F Q
void T(void)
{
    /*0*/ int otimes = 0; /*0*/
_F:
    F();

    /*1*/
    switch (otimes)
    {
    case '*':
        printf("\tmul stack[sp], acc\n", otimes);
        otimes = 0;
        break;
    case '/':
        printf("\tdiv stack[sp], acc\n", otimes);
        otimes = 0;
        break;
    }
    /*1*/

    if (lookahead == '*' || lookahead == '/')
    {
        /*2*/ otimes = lookahead; /*2*/
        match(lookahead);
        goto _F;
    };
}

// F -> (E) | DEC | ID
void F(void)
{
    /*0*/ char varname[MAXIDLEN + 1]; /*0*/

    switch (lookahead)
    {
    case '(':
        match('(');
        E();
        match(')');
        break;
    case NUM:
        /*1*/ printf("\tmov %s, acc\n", lexeme); /*1*/
        acc = strtod(lexeme, NULL);
        match(NUM);
        break;
    case ';':
        match(';');
        break;
    default:
        /*2*/ strcpy(varname, lexeme); /*2*/
        match(ID);
        if (lookahead == ASGN)
        {
            // L-value (variavel de atribuição)
            match(ASGN);
            E();
            /*3*/ printf("\tstore acc,%s\t%f\n", varname, acc); /*3*/
            store(varname, acc);
        }
        else
        {
            ;
            // R-value (variavel de consulta)
            /*4*/
            printf("\tacc = recall(%s)\n", varname);
            acc = recall(varname);
            /*4*/
            printf("%f\n", acc);
        }
    }
}

void match(int expected)
{
    if (lookahead == expected)
        lookahead = gettoken(source);
    else
    {
        fprintf(stderr, "token mismatch: expected %d, got %c ascii(%d)\n", expected, lookahead, lookahead);
        exit(-3);
    }
}
