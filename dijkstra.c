#include <stdbool.h>
#include "fibonacci-heap.h"
#include "heap.h"
#include <limits.h>

void DijkstraFH(
    NODE **NODES, NODE **PI, int s, int NODES_NUMBER, int MAX_DEGREE)
{
    for (int u = 0; u < NODES_NUMBER + 1; u++)
    {
        if (u != s)
        {
            NODES[u]->cost = INT_MAX;
            NODES[u]->state = 0;
            PI[u] = NULL;
        }
    }
    NODES[s]->state = 1, PI[s] = NULL;
    FHEAP *Q = fheapInnit(MAX_DEGREE);
    insertFnode(Q, NODES[s]->fnode);
    while (Q->min_root != NULL)
    {
        NODE *NODO = extractfMin(Q);
        CONN *VECINO = NODES[NODO->id]->conn;
        while (VECINO != NULL)
        {
            NODE *NODO_VECINO = NODES[VECINO->to_id];
            if (NODO_VECINO->state == 0 || NODO_VECINO->state == 1)
            {
                if (NODO_VECINO->cost > NODO->cost + VECINO->cost)
                {
                    NODO_VECINO->cost = NODO->cost + VECINO->cost;
                    PI[NODO_VECINO->id] = NODO;
                    if (NODO_VECINO->state != 0)
                    {
                        decreasefKey(Q, NODO_VECINO, NODO_VECINO->cost);
                    }
                }
                if (NODO_VECINO->state == 0)
                {
                    NODO_VECINO->state = 1;
                    insertFnode(Q, NODES[NODO_VECINO->id]->fnode);
                }
            }
            VECINO = VECINO->next_conn;
        }
        NODO->state = 2;
    }
    free(Q);
}

void DijkstraH(
    NODE **NODES, NODE **PI, int s, int NODES_NUMBER)
{
    for (int u = 0; u < NODES_NUMBER + 1; u++)
    {
        if (u != s)
        {
            NODES[u]->cost = INT_MAX;
            NODES[u]->state = 0;
            PI[u] = NULL;
        }
    }
    NODES[s]->state = 1, PI[s] = NULL;
    HEAP *Q = heapInnit(NODES_NUMBER);
    insertNode(Q, NODES[s]);
    while (Q->array[0] != NULL)
    {
        NODE *NODO = extractMin(Q);
        CONN *VECINO = NODES[NODO->id]->conn;
        while (VECINO != NULL)
        {
            NODE *NODO_VECINO = NODES[VECINO->to_id];
            if (NODO_VECINO->state == 0 || NODO_VECINO->state == 1)
            {
                if (NODO_VECINO->cost > NODO->cost + VECINO->cost)
                {
                    NODO_VECINO->cost = NODO->cost + VECINO->cost;
                    PI[NODO_VECINO->id] = NODO;
                    if (NODO_VECINO->state != 0)
                    {
                        decreaseKey(Q, NODO_VECINO->heap_index, NODO_VECINO->cost);
                    }
                }
                if (NODO_VECINO->state == 0)
                {
                    NODO_VECINO->state = 1;
                    insertNode(Q, NODES[NODO_VECINO->id]);
                }
            }
            VECINO = VECINO->next_conn;
        }
        NODO->state = 2;
    }
    free(Q->array);
    free(Q);
}
