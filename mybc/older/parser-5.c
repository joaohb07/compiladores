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
    int otimes = 0;

    if (lookahead == '+' || lookahead == '-')
    {
        !(lookahead == '-') || (signal = lookahead);
        match(lookahead);
    }
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
        }

    if (signal)
    {
        printf(" neg ");
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
