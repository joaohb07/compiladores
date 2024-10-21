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
#include <calculator.h>

int lookahead;

// oplus = '+' || '-'
// E -> [oplus] T {oplus T}
void E(void)
{

    /*0*/ int oplus = 0, signal = 0; /*0*/
    acc = 0;
    if (lookahead == '+' || lookahead == '-')
    {
        !(lookahead == '-') || (signal = lookahead);
        match(lookahead);
    }
_T:
    T();
    /*1*/
    if (signal)
    {
        acc = -acc;
        signal = 0;
    }
    /*1*/

    /*2*/
    if (oplus)
    {
        switch (oplus)
        {
        case '+':
            acc = calc('+', acc, stack[sp]);
            push(acc);
            break;
        case '-':
            acc = calc('-', acc, stack[sp]);
            push(acc);
            break;
        }
        acc = pop();
        oplus = 0;
    }
    /*2*/

    if (lookahead == '+' || lookahead == '-')
    {
        /*3*/
        oplus = lookahead;
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
        acc = calc('*', acc, stack[sp]);
        push(acc);
        otimes = 0;
        break;
    case '/':
        acc = calc('/', acc, stack[sp]);
        push(acc);
        otimes = 0;
        break;
    }
    /*1*/

    if (lookahead == '*' || lookahead == '/')
    {
        /*2*/ otimes = lookahead; /*2*/
        push(acc);
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
        /*1*/ acc = atof(lexeme); /*1*/
        match(NUM);
        break;
    /*2*/
    case ';':
        match(';');
        break;
    /*2*/
    default:
        /*3*/ strcpy(varname, lexeme); /*3*/
        match(ID);
        if (lookahead == ASGN)
        {
            match(ASGN);
            E();
            /*4*/ store(varname, acc); /*4*/
        }
        else
        {
            /*5*/ acc = recall(varname); /*5*/
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
