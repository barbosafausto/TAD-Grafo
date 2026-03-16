#include "graph.h"
#include <stdio.h>

/*
=== GRUPO ===
15512767 - José Fausto Vital Barbosa
16876293 - João Pedro Boaretto
16897421 - Philippe Sardenberg Castro Couto
16854281 - André Luiz Sousa Paião
*/

void print_matrix(GRAFO* G){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            printf("%d ", adjacency_matrix(G)[i][j]);
        }
        printf("\n");
    }
}

int main() {

    GRAFO *G = MyGraph(5);

    if (!G) printf("NULL\n");
    else printf("Ok!\n");

    add_edge(G, 1, 2, 1);
    add_edge(G, 3, 4, 8);
    print_matrix(G);
    

    return 0;
}