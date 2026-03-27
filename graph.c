#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct grafo {

    int N;
    int** adj_matrix;
};

Graph* MyGraph(int N) {

    Graph* G = (Graph*) malloc(sizeof(Graph));

    G->N = N;

    G->adj_matrix = (int**) malloc((N+1) * sizeof(int*));
    if (!G->adj_matrix) return NULL; //Erro de alocação

    for (int i = 1; i <= N; i++) {

        G->adj_matrix[i] = (int*) malloc((N+1) * sizeof(int));
        if (!G->adj_matrix[i]) return NULL; // Erro de alocação

        memset(G->adj_matrix[i], -1, (N+1)*sizeof(int)); //Inicialização com -1 nas arestas
    }

    return G;
}

bool valid(Graph*G, int u, int v) {

    //Função que valida a entrada
    if (!G || u < 1 || v < 1 || u > G->N || v > G->N) 
        return false;

    return true;
}

bool add_edge(Graph* G, int u, int v, int w) {

    if (valid(G, u, v)) {

        G->adj_matrix[u][v] = G->adj_matrix[v][u] = w;
        return true;
    }
    return false;
}

int_8 exist_edge(Graph* G, int u, int v) {

    if (valid(G, u, v)) {

        return (G->adj_matrix[u][v] == -1) ? 0 : 1;
    }

    return 0;
}

int* neighbors(Graph* G, int u){
    // Implementação da função neighbors com sentinela -1

    if (G == NULL || u < 1 || u > G->N) return NULL; // validar entrada

    int* neighbors = (int*) malloc((G->N+1) * sizeof(int)); // +1 para caso o grafo tenha laço
    if (!neighbors) return NULL; // Erro de alocação

    int count = 0;

    for (int v = 1; v <= G->N; v++) {
        if (G->adj_matrix[u][v] != -1) {
            neighbors[count++] = v;
        }
    }

    neighbors[count] = -1; // Marcador de fim da lista

    return neighbors;
}

int_8 remove_edge(Graph* G, int u, int v){

    if (valid(G, u, v)) {

        if(G->adj_matrix[u][v] != -1) {

            G->adj_matrix[u][v] = G->adj_matrix[v][u] = -1;
            return 1;
        }

        //Aresta não existe, retorna -1
        return -1;
    }
    
    //Erro, retorna -1
    return -1;
}

void print_info(Graph* G) {

    if (!G) return;
    
    //Impressão dos vértices
    printf("V = [");
    for (int i = 1; i <= G->N; i++) {
        
        printf("%d", i);

        if (i != G->N) printf(", ");
    }
    printf("]\n");

    //Impressão das arestas por coluna
    printf("E = [");
    bool first = true;
    for (int j = 1; j <= G->N; j++) {

        //Vizinho do vértice j
        for (int i = 1; i <= j; i++) {

            if (G->adj_matrix[i][j] != -1) {
                
                if (first) {

                    printf("(%d, %d)", i, j);
                    first = false;
                }
                else printf(", (%d, %d)", i, j);
            }
        }
    }
    printf("]\n");
}

bool remove_graph(Graph** G){

    
    if (G == NULL || *G == NULL) return false;

    //Se a matriz existe
    if ((*G)->adj_matrix != NULL) {

        //Vamos percorrer cada linha liberando-a
        for (int i = 1; i <= (*G)->N; i++) {

            free((*G)->adj_matrix[i]);
            (*G)->adj_matrix[i] = NULL;
        }
        
        //Liberamos a matriz
        free((*G)->adj_matrix);
        (*G)->adj_matrix = NULL;
    }

    //Liberamos o grafo
    free(*G);
    *G = NULL;

    return true;
}

int max_neighbors(Graph *G){

    //Se G é NULL, aborta e retorna -1
    if (!G) {
        return -1;
    }

    int neighbors = 0; // Contador: maior número de vizinhos
    int aux = 0;       // Contador: quantidade de vizinhos de vértice atual
    int u = 0;         // Resposta: vértice com mais vizinhos
    
    for(int i = 1; i <= G->N; i++) {

        for(int j = i+1; j <= G->N; j++) { //j = i+1, pois a matriz é simétrica

            //Se tem aresta, é um vizinho a mais
            if(G->adj_matrix[i][j] != -1){
                aux++;
            }
        }

        //Se o vértice i tem mais vizinhos que u, então i é a nova resposta
        if(aux > neighbors){
            u = i;
            neighbors = aux;
        }
        aux = 0;
    }
    
    return u;
}

int** adjacency_matrix(Graph* G){
    
    if (G != NULL)
        return (G->adj_matrix);    
    else
        return NULL;
}