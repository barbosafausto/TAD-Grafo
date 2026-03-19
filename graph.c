#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
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

int** adjacency_matrix(GRAFO* G){
    
    if (G != NULL)
        return (G->adj_matrix);    
    else
        return NULL;
}

bool add_edge(GRAFO* G, int u, int v, int w){
    if (G != NULL && u >= 0 && u < G-> N && v >= 0 && v < G->N) {

        G->adj_matrix[u][v] = G->adj_matrix[v][u] = w;
        return true;
    }
    return false;
}

int_8 remove_edge(GRAFO* G, int u, int v){
    if (G != NULL && u >= 0 && u < G->N && v >= 0 && v < G->N) {

        if(G->adj_matrix[u][v] != -1) {

            G->adj_matrix[u][v] = G->adj_matrix[v][u] = -1;
            return 1;
        }

        printf("-1\n");
        return -1;

    }
    return 0;
}
