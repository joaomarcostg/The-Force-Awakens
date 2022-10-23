#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "operacoes.h"

int ForcaBruta(int *distancia, int n, int k)
{
    int *s;
    s = malloc((n + 1) * sizeof(int));
    s[0] = 0;

    int tam = 0;
    int resultado = 99999;
    while (1)
    {
        if (s[tam] < n)
        {
            s[tam + 1] = s[tam] + 1;
            tam += 1;
        }
        else
        {
            s[tam - 1] += 1;
            tam -= 1;
        }
        if (tam == 0)
            break;

        if (tam == k)
        {
            int aux[tam + 1];
            int j = 0;
            for (j = 0; j < tam; j++)
            {
                aux[j] = somaPosicao(distancia, s[j], s[j + 1]);
            }
            aux[j] = somaPosicao(distancia, s[j], n + 1);
            int maxvalorVet = 0;
            for (int r = 0; r < j + 1; r++)
            {
                if (maxvalorVet < aux[r])
                    maxvalorVet = aux[r];
            }
            if (maxvalorVet < resultado)
            {
                resultado = maxvalorVet;
            }
        }
    }
    free(s);
    return resultado;
}

int AlgoritmoGuloso(int *distancia, int n, int k)
{
    int i, aux, aux2, contdiv, max;
    aux = 0;
    aux2 = 0;
    contdiv = 0;
    max = 0;
    for (i = 0; i <= n; i++)
        aux += distancia[i];

    aux /= (k + 1);
    for (i = 0; i <= n; i++)
    {
        if (aux2 + distancia[i] > aux && contdiv < k)
        {
            if (aux2 + distancia[i] - aux <= aux - aux2)
            {
                aux2 += distancia[i];
                if (aux2 > max)
                    max = aux2;
                aux2 = 0;
                contdiv++;
            }
            else if (aux2 > max)
            {
                max = aux2;
                aux2 = distancia[i];
                contdiv++;
            }
        }
        else
            aux2 += distancia[i];
    }
    if (aux2 > max)
        max = aux2;

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
            int maxesc = INT_MAX;
            int auxesc = INT_MAX;
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
                    if (auxIter2 > auxIter)
                    {
                        if (auxIter2 > maxIter)
                        {
                            if (auxIter2 < maxesc)
                            {
                                maxesc = auxIter2;
                                auxesc = auxIter2;
                            }
                        }
                        else
                        {
                            if (maxIter < maxesc)
                            {
                                maxesc = maxIter;
                                auxesc = auxIter2;
                            }
                        }
                    }
                    else
                    {
                        if (auxIter > maxIter)
                        {
                            if (auxIter < maxesc)
                            {
                                maxesc = auxIter;
                                auxesc = auxIter2;
                            }
                        }
                        else
                        {
                            if (maxIter < maxesc)
                            {
                                maxesc = maxIter;
                                auxesc = auxIter2;
                            }
                        }
                    }
                    auxIter += distancia[cont4];
                }
            }

            aux[cont1][cont2] = auxesc;
            max[cont1][cont2] = maxesc;
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