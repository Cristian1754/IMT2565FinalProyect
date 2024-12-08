#include <stdio.h>
#include "fibonacci-heap.c"

int main()
{
    // Test de Inserción
    int N = 1000;
    NODE* node_list[N];
    int cost;
    for (int i = 0; i < N; i += 1) {
        node_list[i] = nodeInnit(i);
        cost = N + (rand() % N);
        node_list[i]->cost = cost;
    }
    // node_list[N-1]->cost = -1;

    FHEAP* fheap = fheapInnit(N);
    for (int i = 0; i < N; i += 1) {
        FNODE* fnode = fnodeInnit(node_list[i]);
        node_list[i]->fnode = fnode;
        insertFnode(fheap, fnode);
    }



    // printf("\n");

    // Test de extraer mínimo
    // NODE* node;
    // node = extractMin(fheap);
    // printf("\n");
    // node = extractMin(fheap);
    // printf("\n");
    // node = extractMin(fheap);
    // printf("\n");
    // node = extractMin(fheap);
    // printf("\n");
    // node = extractMin(fheap);
    // printf("\n");
    // node = extractMin(fheap);

    // printf("\n");

    // Test de DecreaseKey
    NODE* node;
    node = extractMin(fheap);
    int new_cost;
    for (int i = 0; i < N - 1; i += 1){
        new_cost = rand() % N;
        if (node_list[i] != node){
            decreaseKey(fheap, node_list[i], new_cost);
        }
    }
    
    for (int i = 0; i < N ; i += 1){
        node = extractMin(fheap);
    }
    
    return 0;
}