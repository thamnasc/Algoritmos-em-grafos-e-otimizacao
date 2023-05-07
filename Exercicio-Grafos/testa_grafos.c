/*******************************************
 * Leitura e impressao de grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

void inicializa_vetor(int *v, int n)
{
  for(int i = 0; i < n; i++)
    v[i] = 0;
}

int main() {
  
  // cria grafo vazio
  grafo G = cria_grafo();
  
  // le n e adiciona vertices 1..n
  int n;
  scanf("%d", &n); // qtd vertices
  
  for (int i = 1; i <= n; ++i)
    adiciona_vertice(i, G);
  
  // le pares u v e adiciona arestas {u,v}
  // termina quando digitar 0 0
  int id = 1;
  int u, v;
  scanf("%d %d", &u, &v);
  while (u && v) {
    adiciona_aresta(id, u, v, G);
    ++id;
    scanf("%d %d", &u, &v);
  }
  
  // imprime informacoes do grafo e o destroi
  imprime_grafo(G);

  ///// transforma em subgrafo /////
  int vertices[n];

  inicializa_vetor(vertices, n);

  scanf("%d", &v);

  // atribui 1 ao vértice que vai ser mantido no subgrafo
  while (v)
  {
    vertices[v-1] = 1;
    scanf("%d", &v);
  }

  // retira do grafo os vertices que nao fazem parte do subgrafo
  for(int j = 0; j < n; j++)
    if(!vertices[j])
      remove_vertice((j+1), G);

  imprime_grafo(G);
  destroi_grafo(G);
  
  return 0;
}
