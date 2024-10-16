#include <lexer.h>
#include <ctype.h>
#include <stdlib.h>

// ID = [A-Za-z][A-Za-z0-9]*
int isID(FILE *tape){

    int head = getc(tape);
    if (isalpha(head)){
        while(isalnum(head = getc(tape)));
        ungetc(head, tape); 
        return ID;
    }
    ungetc(head, tape);
    return 0;   
}

// DEC = [1-9][0-9]* | 0
int isDEC(FILE *tape){
    int head = getc(tape);
    if (isdigit(head)){
        if (head == '0'){
            return DEC;
        }
        while(isdigit(head = getc(tape)));
        ungetc(head, tape);
        return DEC;
    }
    ungetc(head, tape);
    return 0;
}

void gettoken(FILE *source ){
    if (isID(source) != 0) printf("It's an ID\n");
    else if (isDEC(source)) printf("It's a decimal integer\n");
    else printf("not an ID nor a decimal integer\n");
}
