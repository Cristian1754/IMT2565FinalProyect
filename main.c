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

    NODE **NODES = calloc(NODES_NUMBER + 1, sizeof(NODE));
    for (int i = 0; i < NODES_NUMBER + 1; i++)
    {
        NODES[i] = nodeInnit(i);
        NODES[i]->fnode = fnodeInnit(NODES[i]);
    }

    int TAIL, HEAD, COST;
    for (int i = 0; i < EDGES_NUMBER; i++)
    {
        fscanf(input_file, "%d", &TAIL);
        fscanf(input_file, "%d", &HEAD);
        fscanf(input_file, "%d", &COST);
        // printf("AÑADIENDO LA CONEXIÓN ENTRE %d y %d\n", TAIL, HEAD);
        addConn(NODES, TAIL, HEAD, COST);
    }

    NODE **PI = calloc(NODES_NUMBER + 1, sizeof(NODE));

    Dijkstra(NODES, PI, 1, NODES_NUMBER, NODES_NUMBER);

    int nodo_llegada = 4000;
    fprintf(output_file, "RUTA PARA LLEGAR DESDE NODO 1 HASTA EL NODO %d con costo %d\n", nodo_llegada, NODES[nodo_llegada]->cost);
    NODE *STATE = NODES[nodo_llegada];
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
