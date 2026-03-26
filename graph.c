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

bool valid(GRAFO*G, int u, int v) {

    if (!G || u < 0 || v < 0 || u >= G->N || v >= G->N) 
        return false;

    return true;
}

int** adjacency_matrix(GRAFO* G){
    
    if (G != NULL)
        return (G->adj_matrix);    
    else
        return NULL;
}

bool add_edge(GRAFO* G, int u, int v, int w) {

    if (valid(G, u, v)) {

        G->adj_matrix[u][v] = G->adj_matrix[v][u] = w;
        return true;
    }
    return false;
}

int_8 exist_edge(GRAFO* G, int u, int v) {

    if (valid(G, u, v)) {

        return (G->adj_matrix[u][v] == -1) ? 0 : 1;
    }

    return 0;
}

int_8 remove_edge(GRAFO* G, int u, int v){

    if (valid(G, u, v)) {

        if(G->adj_matrix[u][v] != -1) {

            G->adj_matrix[u][v] = G->adj_matrix[v][u] = -1;
            return 1;
        }

        printf("-1\n");
        return -1;

    }
    return 0;
}

bool delete_graph(GRAFO** G){

    if (G == NULL || *G == NULL) return false;

    if ((*G)->adj_matrix != NULL){
        for (int i = 0; i < (*G)->N; i++)
        {
            free((*G)->adj_matrix[i]);
            (*G)->adj_matrix[i] = NULL;
        }
        free((*G)->adj_matrix);
        (*G)->adj_matrix = NULL;
    }

    free(*G);
    *G = NULL;

    return true;

}

int max_neighbors(GRAFO *G){
    if(!G){
        return -1;
    }
    int neighbors = 0;
    int aux = 0;
    int u = 0;
    for(int i = 0; i < G->N; i++){
        for(int j = 0; j < G->N; j++){
            if(G->adj_matrix[i][j] != -1){
                aux++;
            }
        }
        if(aux > neighbors){
            u = i;
            neighbors = aux;
        }
        aux = 0;
    }
    return u;
}

int* neighbors(GRAFO* G, int u){
    // Implementação da função neighbors com sentinela -1

    if (G == NULL || u < 0 || u >= G->N) return NULL; // validar entrada

    int* neighbors = (int*) malloc((G->N+1) * sizeof(int)); // +1 para caso o grafo tenha laço
    if (!neighbors) return NULL; // Erro de alocação

    int count = 0;

    for (int v = 0; v < G->N; v++) {
        if (G->adj_matrix[u][v] != -1) {
            neighbors[count++] = v;
        }
    }

    neighbors[count] = -1; // Marcador de fim da lista

    return neighbors;
}
