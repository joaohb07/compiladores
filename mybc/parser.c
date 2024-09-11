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
    int signal = 0;
    int oplus = 0;
    if (lookahead == '+' || lookahead == '-')
    {
        !(lookahead == '-') || (signal = lookahead);
        match(lookahead);
    }
_T:
    T();
    if (signal)
    {
        printf(" neg ", signal);
        signal = 0;
    }
    if (oplus)
    {
        printf(" %c ", oplus);
        oplus = 0;
    }

    if (lookahead == '+' || lookahead == '-')
    {
        oplus = lookahead;
        match(lookahead);
        goto _T;
    }
}

// T -> F Q
void T(void)
{
    int otimes = 0;
_F:
    F();
    if (otimes)
    {
        printf(" %c ", otimes);
        otimes = 0;
    }

    if (lookahead == '*' || lookahead == '/')
    {
        otimes = lookahead;
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
        printf(" %s", lexeme);
        match(OCT);
        break;
    case HEX:
        printf(" %s", lexeme);
        match(HEX);
        break;
    case DEC:
        printf(" %s", lexeme);
        match(DEC);
        break;
    default:
        printf(" %s", lexeme);
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
