#define STACKSIZE 1024

extern double stack[STACKSIZE]; // Pilha
extern int sp;                  // Índice do topo da pilha

double pop();
void push(double val);
