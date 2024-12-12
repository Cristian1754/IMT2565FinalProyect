#pragma once
#include "structures.h"

struct heap;
typedef struct heap HEAP;

struct heap {
    int last;
    int size;
    NODE** array;
};

HEAP* heapInnit(int size);
void insertNode(HEAP* heap, NODE* node);
NODE* extractMin(HEAP* heap);
void swap(HEAP* heap, int index1, int index2);
void siftUp(HEAP* heap, int index);
void siftDown(HEAP* heap, int index);
void decreaseKey(HEAP* heap, int index, int new_cost);