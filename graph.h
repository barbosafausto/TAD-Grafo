#ifndef Graph_H
    #define Graph_H

    #include <stdbool.h>
    #define int_8 char //Definição de inteiro de 8 bits

    typedef struct grafo Graph;

    //Funções abaixo

    //Retorna um grafo de N vértices com 0 arestas.
    Graph* MyGraph(int N); 

    //Criar uma aresta de peso w entre os vértices (u, v).
    //Retorna True se a operação foi bem-sucedida.
    bool add_edge(Graph* G, int u, int v, int w);

    //Retorna 1 se a aresta existe, 0 caso contrário.
    int_8 exist_edge(Graph* G, int u, int v);

    //Retorna um array (ponteiro) contendo os vizinhos do vértice u.
    int* neighbors(Graph* G, int u);

    //Remove a aresta entre dois vértices (u, v). Retorna e escreve -1 caso a aresta não exista.
    int_8 remove_edge(Graph* G, int u, int v);

    //Imprime todos os vértices e arestas do grafo.
    void print_info(Graph* G);

    //Deleta o grafo, i. e., desaloca toda a memória alocada para ele.
    //Retorna True se bem sucedido.
    bool remove_graph(Graph** G);

    //Retorna o vértice com maior número de vizinhos (maior grau).
    int max_neighbors(Graph* G);

    //Retorna a matriz de adjacência do grafo (ponteiro de ponteiro).
    int** adjacency_matrix(Graph* G);

#endif