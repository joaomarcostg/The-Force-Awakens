#include "operacoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int soma(int vet[], int inicio, int fim)
{
    int valor = 0;
    for (int i = inicio; i < fim; i++)
    {
        valor += vet[i];
    }
    return valor;
}

int maior(int vet[], int n){
    int maiorNum = -INT_MAX;
    for(int i=0; i<n; i++){
        if(vet[i] > maiorNum){
            maiorNum = vet[i];
        }
    }
    return maiorNum;
}