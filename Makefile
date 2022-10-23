build:
	gcc forceawakens.c operacoes.c -o tp

run: 
	./tp AG < testes.txt	

start: build run

clean:
	rm *.o	