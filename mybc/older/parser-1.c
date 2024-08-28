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
    if (lookahead == '+' || lookahead == '-')
        match(lookahead);
_T:
    T();
    if (lookahead == '+' || lokahead == '-') 
     {
	 match(lookahead);
	 goto _T;
     }
}

// T -> F Q
void T(void)
{

_F:
    F();
    if (lookahead == '*' || lokahead == '/')
    {
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
	printf(" id ");
        match(OCT);
        break;
    case HEX:
	printf(" hex ");
        match(HEX);
        break;
    case DEC:
	printf(" dec ");
        match(DEC);
        break;
    default:
	printf(" id ");
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