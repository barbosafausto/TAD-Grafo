#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include <stdbool.h>
#define int_8 char //Definição de inteiro de 8 bits

/*
=== GRUPO ===
15512767 - José Fausto Vital Barbosa
16876293 - João Pedro Boaretto
16897421 - Philippe Sardenberg Castro Couto
16854281 - André Luiz Sousa Paião
*/

typedef struct grafo Graph;
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

        for(int j = 1; j <= G->N; j++) { //j = i+1, pois a matriz é simétrica

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

int main() {

    int option;
    int N, x, y, w;
    int res;
    int print_status = 1;
    int** adj_matrix = NULL;
    int u;

    Graph *G = NULL;

    scanf("%d", &option);

    while (option != -1)
    {
        switch (option){

        case 0:
            scanf("%d", &N);
            G = MyGraph(N);
            break;

        case 1:
            // adicionamos
            scanf("%d %d %d", &x, &y, &w);
            add_edge(G, x, y, w);
            break;

        case 2:
            // get
            scanf("%d %d", &x, &y);
            res = exist_edge(G, x, y);
            print_status = 0;
            break;

        case 3:
            scanf("%d", &x);
            
            int* viz = neighbors(G, x);
            if (viz) {

                int i;
                for (i = 0; viz[i] != -1; i++)
                    printf("%d ", viz[i]);
                printf("\n");

                free(viz);
            }
            print_status = -1;

            break;

        case 4:
            
            scanf("%d %d", &x, &y);

            if (remove_edge(G, x, y) == -1) {

                print_status = -1;
                printf("-1\n");
            }

            break;

        case 5: 

            adj_matrix = adjacency_matrix(G);
            printf("Adjacency Matrix:\n");

            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {

                    printf("%*d", 3, (adj_matrix[i][j] == -1) ? 0 : adj_matrix[i][j]);

                    if (j < N) printf(" ");
                }
                printf("\n");
            }

            print_status = -1;
            break;

        case 6:

            u = max_neighbors(G);
            printf("max vertex: %d\n", u);
            print_status = -1;
            break;

        default:
            printf("unrecognized option %d!\n", option);
        }

        scanf("%d", &option);
    }

    if (option == -1) {
        if (print_status == 1)
            print_info(G);
        else if (print_status == 0)
            printf("%d\n", res);

    }

    remove_graph(&G);
    return 0;
}
