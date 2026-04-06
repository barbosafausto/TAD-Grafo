#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include <stdbool.h>
#define int_8 char // Definição de um tipo inteiro de 8 bits usando char para economizar memória

/*
=== GRUPO ===
15512767 - José Fausto Vital Barbosa
16876293 - João Pedro Boaretto
16897421 - Philippe Sardenberg Castro Couto
16854281 - André Luiz Sousa Paião
*/

typedef struct grafo Graph;
struct grafo {
    int N;             // Número total de vértices no grafo
    int** adj_matrix;  // Matriz de adjacência (ponteiro de ponteiros) para armazenar os pesos das arestas
};

// Função para inicializar o grafo e alocar dinamicamente a matriz
Graph* MyGraph(int N) {

    Graph* G = (Graph*) malloc(sizeof(Graph));

    G->N = N;

    // Aloca as linhas da matriz (usando N+1 para que o índice 0 seja ignorado e os vértices vão de 1 a N)
    G->adj_matrix = (int**) malloc((N+1) * sizeof(int*));
    if (!G->adj_matrix) return NULL; // Erro de alocação

    for (int i = 1; i <= N; i++) {

        // Aloca as colunas para a linha atual
        G->adj_matrix[i] = (int*) malloc((N+1) * sizeof(int));
        if (!G->adj_matrix[i]) return NULL; // Erro de alocação

        // Preenche toda a linha alocada com -1 (indicador padrão de "sem aresta")
        memset(G->adj_matrix[i], -1, (N+1)*sizeof(int)); //Inicialização com -1 nas arestas
    }

    return G;
}

// Função auxiliar para validar se os vértices u e v estão dentro dos limites permitidos [1, N]
bool valid(Graph*G, int u, int v) {

    //Função que valida a entrada
    if (!G || u < 1 || v < 1 || u > G->N || v > G->N) 
        return false;

    return true;
}

// Insere uma aresta com peso 'w' no grafo
bool add_edge(Graph* G, int u, int v, int w) {

    if (valid(G, u, v)) {

        // Por ser um grafo não-direcionado, a inserção ocorre nas duas posições simétricas
        G->adj_matrix[u][v] = G->adj_matrix[v][u] = w;
        return true;
    }
    return false;
}

// Checa se os vértices estão conectados
int_8 exist_edge(Graph* G, int u, int v) {

    if (valid(G, u, v)) {

        // Se o valor for -1 (ausência de conexão), retorna 0. Senão, retorna 1.
        return (G->adj_matrix[u][v] == -1) ? 0 : 1;
    }

    return 0;
}

// Retorna um vetor alocado dinamicamente com todos os vizinhos do vértice u
int* neighbors(Graph* G, int u){
    // Implementação da função neighbors com sentinela -1

    if (G == NULL || u < 1 || u > G->N) return NULL; // validar entrada

    int* neighbors = (int*) malloc((G->N+1) * sizeof(int)); // +1 para caso o grafo tenha laço e o sentinela
    if (!neighbors) return NULL; // Erro de alocação

    int count = 0;

    // Percorre a linha referente a u. Se for diferente de -1, o vértice 'v' é vizinho
    for (int v = 1; v <= G->N; v++) {
        if (G->adj_matrix[u][v] != -1) {
            neighbors[count++] = v;
        }
    }

    // Marca o fim da lista com um sentinela -1 para auxiliar na leitura do array retornado
    neighbors[count] = -1; 

    return neighbors;
}

// Remove a aresta entre os vértices reatribuindo -1 na matriz
int_8 remove_edge(Graph* G, int u, int v){

    if (valid(G, u, v)) {

        if(G->adj_matrix[u][v] != -1) {

            // Remoção em ambas as posições 
            G->adj_matrix[u][v] = G->adj_matrix[v][u] = -1;
            return 1;
        }

        //Aresta não existe, retorna -1
        return -1;
    }
    
    //Erro, retorna -1
    return -1;
}

// Exibe informações formatadas sobre os conjuntos de Vértices (V) e Arestas (E)
void print_info(Graph* G) {

    if (!G) return;
    
    //Impressão dos vértices (1 até N)
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

        //Vizinho do vértice j (limitando i <= j para não imprimir a mesma aresta duas vezes)
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

// Função responsável por liberar toda a memória alocada, evitando Memory Leaks
bool remove_graph(Graph** G){

    
    if (G == NULL || *G == NULL) return false;

    //Se a matriz existe
    if ((*G)->adj_matrix != NULL) {

        //Vamos percorrer cada linha liberando os arrays internos
        for (int i = 1; i <= (*G)->N; i++) {

            free((*G)->adj_matrix[i]);
            (*G)->adj_matrix[i] = NULL;
        }
        
        //Liberamos a matriz
        free((*G)->adj_matrix);
        (*G)->adj_matrix = NULL;
    }

    //Liberamos a estrutura do grafo em si
    free(*G);
    *G = NULL; 

    return true;
}

// Computa e retorna o vértice com o maior grau 
int max_neighbors(Graph *G){

    //Se G é NULL, aborta e retorna -1
    if (!G) {
        return -1;
    }

    int neighbors = 0; // Contador: maior número de vizinhos 
    int aux = 0;       // Contador: quantidade de vizinhos do vértice atual no laço
    int u = 0;         // Resposta: guarda o índice do vértice com mais vizinhos
    
    for(int i = 1; i <= G->N; i++) {

        for(int j = 1; j <= G->N; j++) { 

            //Se tem aresta (é diferente de -1), é um vizinho a mais
            if(G->adj_matrix[i][j] != -1){
                aux++;
            }
        }

        //Se o vértice i atual bateu o maior, atualizamos a resposta
        if(aux > neighbors){
            u = i;
            neighbors = aux;
        }
        aux = 0; // Reseta o auxiliar para contar os vizinhos da próxima iteração de i
    }
    
    return u;
}

// Retorna o ponteiro para a matriz bidimensional interna do TAD
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
    int print_status = 1; // Variável de estado para ditar o que ocorre quando a execução encerra
    int** adj_matrix = NULL;
    int u;

    Graph *G = NULL;

    // Lê a primeira instrução
    scanf("%d", &option);

    // Loop de eventos que roda até receber -1
    while (option != -1)
    {
        switch (option){

        case 0:
            // Criação do Grafo
            scanf("%d", &N);
            G = MyGraph(N);
            break;

        case 1:
            // adicionamos a aresta (u, v) de peso w
            scanf("%d %d %d", &x, &y, &w);
            add_edge(G, x, y, w);
            break;

        case 2:
            // Verifica a aresta
            scanf("%d %d", &x, &y);
            res = exist_edge(G, x, y);
            print_status = 0; // Muda status para imprimir apenas o 'res' no fim
            break;

        case 3:
            // Obtém e imprime vizinhos
            scanf("%d", &x);
            
            int* viz = neighbors(G, x);
            if (viz) {

                int i;
                // Laço para imprimir o vetor até encontrar o sentinela -1
                for (i = 0; viz[i] != -1; i++)
                    printf("%d ", viz[i]);
                printf("\n");

                free(viz); // Importante: Limpa a memória do vetor gerado na função
            }
            print_status = -1; // Silencia o print final do main

            break;

        case 4:
            // Tenta remover uma aresta
            scanf("%d %d", &x, &y);

            // Caso a aresta não exista, imprime -1
            if (remove_edge(G, x, y) == -1) {

                print_status = -1;
                printf("-1\n");
            }

            break;

        case 5: 
            // Imprime graficamente a matriz de adjacência
            adj_matrix = adjacency_matrix(G);
            printf("Adjacency Matrix:\n");

            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {

                    // Substitui o -1 na impressão por 0
                    printf("%*d", 3, (adj_matrix[i][j] == -1) ? 0 : adj_matrix[i][j]);

                    if (j < N) printf(" ");
                }
                printf("\n");
            }

            print_status = -1;
            break;

        case 6:
            // Encontra e imprime o vértice com maior número de arestas
            u = max_neighbors(G);
            printf("max vertex: %d\n", u);
            print_status = -1;
            break;

        default:
            printf("unrecognized option %d!\n", option);
        }

        // Continua consumindo as opções de entrada
        scanf("%d", &option);
    }

    // Ao fim do loop, decide o que precisa ser impresso baseado no histórico da execução
    if (option == -1) {
        if (print_status == 1)
            print_info(G);
        else if (print_status == 0)
            printf("%d\n", res);

    }

    // Libera a memória 
    remove_graph(&G);
    return 0;
}