#include <stdio.h>
#include <stdlib.h>

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

/* lê pares de vértices vizinhos para representar na matriz de adjacência */
/* finaliza lendo 0 0 */
int **criaMatAdj (int n)
{
    int u, v;
    int **matriz = alocaMatriz(n, n);

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
    printf ("\n");
}


void desalocaMatriz (int **matriz)
{
    free (matriz[0]);
    free (matriz);
}

int **multiplicaMats (int **matA, int **matB, int lin, int col)
{
    int **result = alocaMatriz (lin, col);

    int resultI, resultJ, index, n = lin;

    for (resultI = 0; resultI < lin; resultI++)
    {
        for (resultJ = 0; resultJ < col; resultJ++)
        {
            for (index = 0; index < n; index++)
                result[resultI][resultJ] += matA[resultI][index] * matB[index][resultJ]; 
        }
    }

    return result;
}

int main () 
{
    int n, u, v, caminho, arestas = 2;
    int **matAdj, **matA = NULL, **matResult;

    /* lê tamanho da matriz, que é a quantidade de vértices */
    scanf ("%d", &n);

    matAdj = criaMatAdj (n);
    imprimeMatriz (matAdj, n, n);

    /* lê par de vértices qualquer */
    scanf ("%d%d", &u, &v);

    /* encontra menor número de arestas necessárias para chegar de um vértice a outro */

    caminho = matAdj[u-1][v-1];
    /* caso os vértices sejam vizinhos, não é preciso multiplicar matrizes */
    if (caminho) 
    {
        printf ("Eh preciso de 1 aresta para ir do vértice %d ao %d\n", u, v);
        desalocaMatriz (matAdj);
        return 0;
    }

    matResult = multiplicaMats (matAdj, matAdj, n, n);
    caminho = matResult[u-1][v-1];

    while (!caminho)
    {
        arestas++;
        matA = matResult;

        matResult = multiplicaMats (matA, matAdj, n, n);
        imprimeMatriz (matResult, n, n);

        caminho = matResult[u-1][v-1];

        desalocaMatriz (matA);
    }
    printf ("Eh preciso de %d arestas para ir do vértice %d ao %d\n", arestas, u, v);
    

    desalocaMatriz (matAdj);
    desalocaMatriz (matResult);

    return 0;
}