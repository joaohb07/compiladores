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
        match(lookahead);
_T:

_F:
    switch (lookahead)
    {
    case '(':
        match('(');
        E();
        match(')');
        break;
    case OCT:
        match(OCT);
        break;
    case HEX:
        match(HEX);
        break;
    case DEC:
        match(DEC);
        break;
    default:
        match(ID);
    }

    if (lookahead == '*' || lookahead == '/')
    {
        match(lookahead);
        goto _F;
    }

    if (lookahead == '+' || lookahead == '-')

    {
        match(lookahead);
        goto _T;
    }
}

void match(int expected)
{
    if (lookahead == expected)
        lookahead = gettoken(source);
    else
    {
        fprintf(stderr, "token mismatch at line %d\n", linenum);
        exit(-3);
    }
}
