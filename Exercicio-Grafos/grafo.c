/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {  
  vertice v;
  aresta a;
  while (!vazio(G->vertices))
  {
    v = (vertice) desempilha(G->vertices);
    remove_vertice(vertice_id(v), G);
  }
/*   while (!vazio(G->arestas))
  {
    a = desempilha(G->arestas);
    remove_aresta(a, G);
  } */
  free(G->arestas);
  free(G->vertices);
  free(G);
}

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {
  vertice V = (vertice) malloc(sizeof(t_vertice));
  if (!V)
    exit(_ERRO_MALLOC_);
  V->id = id;
  V->fronteira = cria_lista();
  empilha(V, vertices(G));
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  //primeiro remove a aresta, depois o vertice, para não perder o obj
  vertice V = (vertice) (busca_chave(id, vertices(G), (int_f_obj) vertice_id));
  aresta cont_AdeV, cont_AdeG;
  printf("teste1\n\n");
  no aresta_G = primeiro_no(arestas(G));
  printf("teste2\n\n");
  no aresta_V = primeiro_no(fronteira(V));
  printf("teste3\n\n");
  // percorre a lista de fronteira do vértice a ser removido
  while (aresta_V != NULL)
  {
    // percorre a lista de arestas do grafo
    while (aresta_G != NULL)
    {
      cont_AdeV = (aresta) (conteudo(aresta_V));
      cont_AdeG = (aresta) (conteudo(aresta_G));
      // se a aresta da vez for {U, V}
      if (cont_AdeG == cont_AdeV)
      {
        // remove aresta {U, V} de cada vértice
        remove_chave(aresta_id(cont_AdeV), fronteira(vertice_u(cont_AdeV)), (int_f_obj) aresta_id);
        printf("teste4\n\n");
        remove_chave(aresta_id(cont_AdeV), fronteira(vertice_v(cont_AdeV)), (int_f_obj) aresta_id);
        printf("teste5\n\n");
        // remove aresta {U, V} do grafo
        remove_aresta(aresta_id(cont_AdeG), G);
      }
      aresta_G = proximo(aresta_G);
    }
    aresta_V = proximo(aresta_V);
  }
  // remove V da lista de vertices do grafo
  remove_chave(id, vertices(G), (int_f_obj) vertice_id);
  free(V->fronteira);
  free(V);
}

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
  aresta A = (aresta) malloc(sizeof(t_aresta));
  if (!A)
    exit(_ERRO_MALLOC_);
  A->id = id;
  A->u = (vertice) (busca_chave(u_id, vertices(G), (int_f_obj) vertice_id));
  A->v = (vertice) (busca_chave(v_id, vertices(G), (int_f_obj) vertice_id));
  printf("testeAresta1\n\n");
  empilha(A, fronteira(vertice_u(A)));
  printf("testeAresta2\n\n");
  empilha(A, fronteira(vertice_v(A)));
  printf("testeAresta3\n\n");
  empilha(A, arestas(G));
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  aresta A = (aresta) (remove_chave(id, arestas(G), (int_f_obj) aresta_id));
  free(A);
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:{%d,%d}", aresta_id(e), u_id, v_id);
}
