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
#include <lexer.h>
#include <string.h>
#include <symtab.h>
#include <parser.h>
#include <stack.h>

int lookahead;
double acc; // acumulador

double calc(char signal,double acc, double stackValue){
    switch (signal)
    {
    case '+':
        return stackValue + acc;
    case '-':
        return stackValue - acc;
    case '*':
        return stackValue * acc;
    case '/':
        if (acc == 0) return 0;
        return stackValue / acc;
    default:
        break;
    }
};

// oplus = '+' || '-'
// E -> [oplus] T {oplus T}
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
            acc = calc('+', acc, stack[sp]);
            push(acc);
            break;
        case '-':
            printf("\tsub acc, stack[sp]\n");
            acc = calc('-', acc, stack[sp]);
            push(acc);
            break;
        }
        printf("\tpop acc\n");
        acc = pop();
        oplus = 0;
    }
    /*2*/

    if (lookahead == '+' || lookahead == '-')
    {
        /*3*/
        oplus = lookahead;
        printf("\tpush acc\n");
        push(acc);
        /*3*/
        match(lookahead);
        goto _T;
    }
}

// T -> F {otimes F}
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
        acc = calc('*', acc, stack[sp]);
        push(acc);
        otimes = 0;
        break;
    case '/':
        printf("\tdiv stack[sp], acc\n", otimes);
        acc = calc('/', acc, stack[sp]);
        push(acc);
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

// F -> (E) | NUM | ID
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
