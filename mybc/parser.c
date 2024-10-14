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
#include <parser.h>
int lookahead;

/* LL(1) grammar:
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
    /*E0*/ int oplus = 0; /*E0*/
    if (lookahead == '+' || lookahead == '-')
    {
        !(lookahead == '-') || (oplus = lookahead);
        match(lookahead);
    }
_T:
    T();
    /*E1*/
    if (oplus)
    {
        printf(" %c ", oplus);
        oplus = 0;
    }
    /*E1*/

    if (lookahead == '+' || lookahead == '-')
    {
        /*E2*/ oplus = lookahead; /*E2*/
        match(lookahead);
        goto _T;
    }
}

// T -> F Q
void T(void)
{
    /*T0*/ int otimes = 0; /*T0*/
_F:
    F();

    /*T1*/
    if (otimes)
    {
        printf(" %c ", otimes);
        otimes = 0;
    }
    /*T1*/

    if (lookahead == '*' || lookahead == '/')
    {
        /*T2*/ otimes = lookahead; /*T2*/
        match(lookahead);
        goto _F;
    };
}

// F -> (E) | DEC | ID
void F(void)
{
    switch (lookahead)
    {
    case '(':
        match('(');
        E();
        match(')');
        break;
    case OCT:
        /*F0*/ printf(" %s", lexeme); /*F0*/
        match(OCT);
        break;
    case HEX:
        /*F0*/ printf(" %s", lexeme); /*F0*/
        match(HEX);
        break;
    case DEC:
        /*F0*/ printf(" %s", lexeme); /*F0*/
        match(DEC);
        break;
    default:
        /*F0*/ printf(" %s", lexeme); /*F0*/
        match(ID);
    }
}

void match(int expected)
{
    if (lookahead == expected)
        lookahead = gettoken(source);
    else
    {
        fprintf(stderr, "token mismatch\n");
        exit(-3);
    }
}
