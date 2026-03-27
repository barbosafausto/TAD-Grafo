#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/*
=== GRUPO ===
15512767 - José Fausto Vital Barbosa
16876293 - João Pedro Boaretto
16897421 - Philippe Sardenberg Castro Couto
16854281 - André Luiz Sousa Paião
*/

int main() {

    int option;
    int N, x, y, w;
    int res;
    int print_status = 1;

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

            if(remove_edge(G, x, y) == -1) {

                print_status = -1;
           printf("-1\n");
            }

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