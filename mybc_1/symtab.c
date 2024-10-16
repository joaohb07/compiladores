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
 *  //descrição do symtab.c
 ***************************************************/
#include <string.h>
#include <symtab.h>

double vmem[SYMTABSIZE];
char symtab[SYMTABSIZE][MAXIDLEN + 1];
int symtab_next_entry = 0;

/*
    lookup procura um nome na tabela de simbolos e retorna seu indice, caso não encontrar, retorna -1
*/
int lookup(char *varname)
{
    int i = 0;
    for (i = 0; i < symtab_next_entry; i++)
    {
        if (strcmp(varname, symtab[i]) == 0)
            break;
    }
    if (i == symtab_next_entry)
    {
        return -1; // no achou varname em symtab
    }
    return i;
}

/*
    store registra uma nova variavel armazenando seu nome em symtab e seu valor em vmem
*/
void store(char *varname, double value)
{
    // vê se varname existe em symtab
    int i = lookup(varname);

    // caso não existir, registra a nova variavel
    //      symtab[i] ← varname
    //      vem[i]← value
    if (i < 0)
    {
        i = symtab_next_entry;
        strcpy(symtab[i], varname);
        vmem[i] = value;
    }
    symtab_next_entry++;
}

double recall(char *varname)
{
    int i = lookup(varname);
    
    if (i < 0)
    {
        return 0.0;
    }
    else
    {
        return vmem[i];
    }
}