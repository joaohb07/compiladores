###################################################
# Compiladores - Noturno - 2024
# Professor Eraldo Pereira Marinho
# 
# Mybc
# 
# Grupo:
# Cristian Santos de Castro
# João Henrique Botelho
# João Pedro Brum Terra
###################################################
CFLAGS = -I. -g

relocatable = mybc.o lexer.o parser.o symtab.o calculator.o

mybc: $(relocatable)
	$(CC) -o mybc $(relocatable) -lm
clean: 
	$(RM) *.o mybc
mostlyclean:
	$(RM) *.o mybc

