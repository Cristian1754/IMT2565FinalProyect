#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"

static bool check_arguments(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
        printf("Donde:\n");
        printf("\tINPUT es la ruta del archivo de input\n");
        printf("\tOUTPUT es la ruta del archivo de output\n");
        exit(1);
    }
    return true;
}

int main(int argc, char **argv)
{
    check_arguments(argc, argv);

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    int NODES_NUMBER;
    fscanf(input_file, "%d", &NODES_NUMBER);
    // fprintf(output_file, "NODES_NUMBER: %d\n", NODES_NUMBER);

    int EDGES_NUMBER;
    fscanf(input_file, "%d", &EDGES_NUMBER);
    // fprintf(output_file, "EDGES_NUMBER: %d\n", EDGES_NUMBER);

    /*=========================================*/
    // Seleccionar la edd
    bool fiboheap = true;
    /*=========================================*/

    NODE **NODES = calloc(NODES_NUMBER + 1, sizeof(NODE));
    for (int i = 0; i < NODES_NUMBER + 1; i++)
    {
        NODES[i] = nodeInnit(i);
        if (fiboheap)
        {
            NODES[i]->fnode = fnodeInnit(NODES[i]);
        }
    }

    int TAIL, HEAD, COST;
    for (int i = 0; i < EDGES_NUMBER; i++)
    {
        fscanf(input_file, "%d", &TAIL);
        fscanf(input_file, "%d", &HEAD);
        fscanf(input_file, "%d", &COST);
        addConn(NODES, TAIL, HEAD, COST);
    }

    // Máximo grado del fheap
    int MAX_DEGREE = 30;
    NODE **PI = calloc(NODES_NUMBER + 1, sizeof(NODE));
    // Nodo raíz y si se quiere un nodo de llegada
    int start = 1;
    int end = 1;
    if (fiboheap)
    {
        DijkstraFH(NODES, PI, start, NODES_NUMBER, MAX_DEGREE);
    }
    else
    {
        DijkstraH(NODES, PI, start, NODES_NUMBER);
    }

    fprintf(output_file, "RUTA PARA LLEGAR DESDE NODO %d HASTA EL NODO %d con costo %d\n", start, end, NODES[end]->cost);
    NODE *STATE = NODES[end];
    while (STATE != NULL)
    {
        fprintf(output_file, "NODO %d\n", STATE->id);
        STATE = PI[STATE->id];
    }

    // LIBERAR MEMORIA
    free(NODES[0]->fnode);
    for (int i = 0; i < NODES_NUMBER + 1; i++)
    {
        nodeFree(NODES[i]);
    }
    free(NODES);
    free(PI);

    /* Cerrar archivos */
    fclose(input_file);
    fclose(output_file);

    return 0;
}
