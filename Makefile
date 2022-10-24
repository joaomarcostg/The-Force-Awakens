build:
	gcc forceawakens.c operacoes.c -o tp

run: 
	./tp $(ALG) < testes.txt	

## use 'make start ALG={...}' para buildar e executar, substituindo {...} por AG | FB | PD
start: build run

clean:
	rm *.o	