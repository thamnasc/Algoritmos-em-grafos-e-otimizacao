#include <stdio.h>
#include <stdlib.h>

int **preencheMatAdj (int **matriz)
{
    int u, v;

    scanf ("%d %d", &u, &v);
    
    while (u && v)
    {
        matriz[u-1][v-1] = 1;
        matriz[v-1][u-1] = 1;

        scanf ("%d %d", &u, &v);
    }

    return matriz;
}

void imprimeMatriz (int **matriz, int lin, int col)
{
    int i, j;

    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
            printf ("%d ", matriz[i][j]);
        printf ("\n");
    }
    print ("\n");
}

int **alocaMatriz (int lin, int col)
{
    int i;
    int **matriz;

    /* aloca vetor de ponteiros de linhas da matriz */
    matriz = malloc (lin * sizeof (int*));
    /* aloca num vetor todos os elementos da matriz */
    matriz[0] = calloc (lin * col, sizeof (int));

    /* ajusta ponteiros de linhas */
    for (i = 1; i < lin; i++)
        matriz[i] = matriz[0] + i * col;
    
    return matriz;
}

int **multiplicaMats (int **matriz, int lin, int col)
{
    int **result = alocaMatriz (lin, col);

    int resultI, resultJ, nElem, n = lin;

    for (resultI = 0; resultI < lin; resultI++)
    {
        for (resultJ = 0; resultJ < col; resultJ++)
        {
            for (nElem = 0; nElem < n; nElem++)
                result[resultI][resultJ] += matriz[resultI][nElem] * matriz[nElem][resultJ]; 
        }
    }

    return result;
}

int main () 
{
    int n;
    int **matriz, **result;

    scanf ("%d", &n);

    matriz = alocaMatriz (n, n);
    preencheMatAdj (matriz);
    imprimeMatriz (matriz, n, n);

    result = multiplicaMats (matriz, n, n);
    imprimeMatriz (result, n, n);

    free (result[0]);
    free (result);
    free (matriz[0]);
    free (matriz);

    return 0;
}