build:
	gcc forceawakens.c operacoes.c -o tp

run: 
	./tp FB < testes.txt	

start: build run

clean:
	rm *.o	