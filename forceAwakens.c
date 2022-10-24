#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "operacoes.h"
#define TRUE 1

int ForcaBruta(int *distancia, int n, int k)
{
    int *vet;
    vet = malloc((n + 1) * sizeof(int));
    vet[0] = 0;

    int tam = 0;
    int resultado = INT_MAX;
    while (TRUE)
    {
        if (vet[tam] < n)
        {
            vet[tam + 1] = vet[tam] + 1;
            tam += 1;
        }
        else
        {
            vet[tam - 1] += 1;
            tam -= 1;
        }
        if (tam == 0)
            break;

        if (tam == k)
        {
            int aux[tam + 1];
            int i = 0;
            while (i < tam)
            {
                aux[i] = soma(distancia, vet[i], vet[i + 1]);
                i++;
            }
            aux[i] = soma(distancia, vet[i], n + 1);
            int maiorValor = maior(aux, (i + 1));
            if (maiorValor < resultado)
            {
                resultado = maiorValor;
            }
        }
    }
    free(vet);
    return resultado;
}

int AlgoritmoGuloso(int *distancia, int n, int k)
{
    int i = 0, aux = 0, visitados = 0, max = 0;
    int distanciaTotal = soma(distancia, 0, n + 1);

    int distanciaMin = distanciaTotal / (k + 1);
    for (i = 0; i <= n; i++)
    {
        if (aux + distancia[i] > distanciaMin && visitados < k)
        {
            if (aux + distancia[i] - distanciaMin <= distanciaMin - aux)
            {
                aux += distancia[i];
                if (aux > max)
                    max = aux;
                aux = 0;
                visitados++;
            }
            else if (aux > max)
            {
                max = aux;
                aux = distancia[i];
                visitados++;
            }
        }
        else
            aux += distancia[i];
    }
    if (aux > max)
        max = aux;

    return max;
}

int ProgramacaoDinamica(int *distancia, int n, int k)
{
    int aux[n + 1][k + 1];
    int max[n + 1][k + 1];
    int cont1 = 1, cont2, cont3, cont4;
    aux[0][0] = distancia[0];
    max[0][0] = distancia[0];
    while (cont1 <= n)
    {
        aux[cont1][0] = aux[cont1 - 1][0] + distancia[cont1];
        max[cont1][0] = aux[cont1][0];

        cont1++;
    }

    for (cont1 = 1; cont1 <= n; cont1++)
    {
        for (cont2 = 1; cont2 <= k; cont2++)
        {
            if (cont2 > cont1)
            {
                aux[cont1][cont2] = aux[cont1][cont2 - 1];
                max[cont1][cont2] = max[cont1][cont2 - 1];
                continue;
            }
            int maxEsc = INT_MAX;
            int auxEsc = INT_MAX;
            int auxIter, auxIter2, maxIter, distanciaMax;

            for (cont3 = cont2 - 1; cont3 < cont1; cont3++)
            {
                maxIter = max[cont3][cont2 - 1];
                auxIter = aux[cont3][cont2 - 1];
                distanciaMax = aux[cont3][cont2 - 1];
                for (cont4 = cont3 + 1; cont4 <= cont1; cont4++)
                    distanciaMax += distancia[cont4];
                for (cont4 = cont3 + 1; cont4 <= cont1; cont4++)
                {
                    auxIter2 = distanciaMax - auxIter;
                    auxEsc = auxIter2;
                    int comparacao[3] = {maxIter, auxIter, auxIter2};
                    // Compara maxIter, auxIter e auxIter2, retornando o maior entre eles
                    int maiorNum = maior(comparacao, 3);
                    if (maiorNum < maxEsc)
                    {
                        maxEsc = maiorNum;
                    }
                    auxIter += distancia[cont4];
                }
            }
            aux[cont1][cont2] = auxEsc;
            max[cont1][cont2] = maxEsc;
        }
    }
    return max[n][k];
}

int main(int argc, char *argv[])
{
    // t = Número de instâncias do problema a serem simuladas
    int t;
    scanf("%d", &t);
    for (int cont = 0; cont < t; cont++)
    {
        // n = planetas consecutivos
        // k = planetas a serem reconquistados
        int n, k;
        scanf("%d %d", &n, &k);
        if (n == 0 || n > 500 || k > 250)
            break;
        int *distancia = malloc((n + 1) * sizeof(int));

        for (int cont2 = 0; cont2 <= n; cont2++)
        {
            int aux;
            scanf("%d", &aux);
            distancia[cont2] = aux;
        }
        if (strcmp(argv[1], "PD") == 0)
            printf("%d\n", ProgramacaoDinamica(distancia, n, k));
        else if (strcmp(argv[1], "AG") == 0)
            printf("%d\n", AlgoritmoGuloso(distancia, n, k));
        else if (strcmp(argv[1], "FB") == 0)
            printf("%d\n", ForcaBruta(distancia, n, k));
        free(distancia);
    }
    return 0;
}