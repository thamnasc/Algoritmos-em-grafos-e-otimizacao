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
  vertice V;
  aresta A;
  while (!vazio(G->vertices))
  {
    V = (vertice) topo(G->vertices);
    remove_vertice(vertice_id(V), G);
  }

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
  vertice V = (vertice) (busca_chave(id, vertices(G), (int_f_obj) vertice_id));
  aresta A;
  vertice u_A, v_A;

  while(!vazio(fronteira(V)))
  {
    A = (aresta) topo(fronteira(V));
    u_A = vertice_u(A);
    v_A = vertice_v(A);
    remove_chave(aresta_id(A), fronteira(u_A), (int_f_obj) aresta_id);
    remove_chave(aresta_id(A), fronteira(v_A), (int_f_obj) aresta_id);
    remove_aresta(aresta_id(A), G);
  }
  remove_chave(vertice_id(V), vertices(G), (int_f_obj) vertice_id);
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
