#pragma once
#include "structures.c"

struct fheap; typedef struct fheap FHEAP;

struct fheap{
    FNODE* min_root;
    int max_degree;
    int number_of_roots;
};

FHEAP* fheapInnit(int max_degree);
void insertFnode(FHEAP* fheap, FNODE* fnode);
FNODE* fnodeUnion(FNODE* fnode1, FNODE* fnode2);
void moveToRoot(FHEAP* fheap, FNODE* fnode);
void cutOutFnode(FHEAP* fheap, FNODE* fnode);
void decreaseKey(FHEAP* fheap, NODE* key_node, int new_cost);
NODE* extractMin(FHEAP* fheap);
void condenseRoots(FHEAP* fheap);
void insertInBuffer(FNODE* buffer[], FNODE* fnode);