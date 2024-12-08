#include <stdio.h>
#include "fibonacci-heap.c"
#include "fibonacci-heap.h"

int main()
{
    // Test de Inserción
    int N = 10;
    NODE* node_list[N];
    for (int i = 0; i < N; i += 1) {
        node_list[i] = nodeInnit(i);
        node_list[i]->cost = (2*N) - i;
    }

    FHEAP* fheap = fheapInnit(5);
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
    for (int i = 0; i < N - 1; i += 1){
        decreaseKey(fheap, node_list[i], i);
    }
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    node = extractMin(fheap);
    
    return 0;
}