#include "graph.h"
#include <stdlib.h>
#include <string.h>

struct grafo {

    int N;
    int** adj_matrix;
};

GRAFO* MyGraph(int N) {

    GRAFO* G = (GRAFO*) malloc(sizeof(GRAFO));

    G->N = N;

    G->adj_matrix = (int**) malloc(N * sizeof(int*));
    if (!G->adj_matrix) return NULL; //Erro de alocação

    for (int i = 0; i < N; i++) {

        G->adj_matrix[i] = (int*) malloc(N * sizeof(int));
        if (!G->adj_matrix[i]) return NULL; // Erro de alocação

        memset(G->adj_matrix[i], -1, N*sizeof(int)); //Inicialização com -1 nas arestas
    }

    return G;
}
