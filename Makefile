operacoes: operacoes.o main.o
	gcc operacoes.o main.o -o tp
main.o: main.c operacoes.h
	gcc -g -c main.c
operacoes.o: operacoes.h operacoes.c
	    gcc -g -c operacoes.c 
clean:
	rm tp
	rm *.o *.gch
