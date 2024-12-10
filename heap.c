#pragma once
#include "heap.h"

HEAP* heapInnit(int size) {

    HEAP* heap = calloc(1,sizeof(HEAP));
    heap->size = size;
    heap->last = 0;
    heap->array = calloc(size, sizeof(NODE*));

    for (int i = 0; i < size; i++) { heap->array[i] = NULL;}

    return heap;
};

void insertNode(HEAP* heap, NODE* node) {

    heap->array[heap->last] = node;
    node->heap_index = heap->last;
    heap->last = heap->last + 1;
    siftUp(heap,node->heap_index);
}

NODE* extractMin(HEAP* heap) {

    if (heap->last == 0) { return NULL;}

    NODE* min_node = heap->array[0];
    heap->array[0] = NULL;
    swap(heap, 0, heap->last - 1);
    heap->last = heap->last - 1;
    return min_node;
}

void swap(HEAP* heap, int index1, int index2) {

    NODE* node1 = heap->array[index1];
    NODE* node2 = heap->array[index2];
    heap->array[index1] = node2;
    heap->array[index2] = node1;
}

void siftUp(HEAP* heap, int index) {

    if (index == 0) { return;}

    int parent_index = (index - 1)/2;
    NODE* node = heap->array[index];
    NODE* parent = heap->array[parent_index];

    if (node->cost < parent->cost) {
        swap(heap, index, parent_index);
        siftUp(heap, parent_index);
    }
}

void decreaseKey(HEAP* heap, int index, int new_cost) {

    heap->array[index]->cost = new_cost;
    siftUp(heap, index);
}