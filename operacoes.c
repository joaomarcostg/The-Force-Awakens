#include "operacoes.h"

int somaPosicao(int vet[], int inicio, int fim)
{
    int valor = 0;
    for (int i = inicio; i < fim; i++)
    {
        valor += vet[i];
    }
    return valor;
}