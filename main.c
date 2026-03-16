#include "graph.h"
#include <stdio.h>

/*
=== GRUPO ===
15512767 - José Fausto Vital Barbosa
16876293 - João Pedro Boaretto
16897421 - Philippe Sardenberg Castro Couto
16854281 - André Luiz Sousa Paião
*/


int main() {

    GRAFO *G = MyGraph(5);

    if (!G) printf("NULL\n");
    else printf("Ok!\n");
    

    return 0;
}