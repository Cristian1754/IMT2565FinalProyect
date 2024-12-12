#pragma once
#include "heap.h"

HEAP *heapInnit(int size)
{
    HEAP *heap = calloc(1, sizeof(HEAP));
    heap->size = size;
    heap->last = 0;
    heap->array = calloc(size, sizeof(NODE *));

    for (int i = 0; i < size; i++)
    {
        heap->array[i] = NULL;
    }

    return heap;
};

void insertNode(HEAP *heap, NODE *node)
{
    heap->array[heap->last] = node;
    node->heap_index = heap->last;
    heap->last = heap->last + 1;
    siftUp(heap, node->heap_index);
}

NODE *extractMin(HEAP *heap)
{
    if (heap->last == 0)
    {
        return NULL;
    }
    NODE *min_node = heap->array[0];
    heap->array[0] = NULL;
    swap(heap, 0, heap->last - 1);
    heap->last = heap->last - 1;
    siftDown(heap, 0);
    return min_node;
}

void swap(HEAP *heap, int index1, int index2)
{
    if (index1 == index2) { return;}

    NODE *node1 = heap->array[index1];
    NODE *node2 = heap->array[index2];
    heap->array[index1] = node2;
    heap->array[index2] = node1;

    node1->heap_index = index2;
    node2->heap_index = index1;
}

void siftUp(HEAP *heap, int index)
{
    if (index == 0)
    {
        return;
    }

    int parent_index = (index - 1) / 2;
    NODE *node = heap->array[index];
    NODE *parent = heap->array[parent_index];

    if (node->cost < parent->cost)
    {
        swap(heap, index, parent_index);
        siftUp(heap, parent_index);
    }
}

void siftDown(HEAP* heap, int index) {

    int lchild_index = (2*index) + 1;
    int rchild_index = (2*index) + 2;
    NODE* min_child_node;
    int min_child_index;

    if (lchild_index >= heap->size || rchild_index >= heap->size){ return;}
    if (heap->array[lchild_index] == NULL) { return;}

    if (heap->array[rchild_index] == NULL){
        min_child_node = heap->array[lchild_index];
        min_child_index = lchild_index;
    } else {
        if (heap->array[lchild_index]->cost < heap->array[rchild_index]->cost) {
            min_child_node = heap->array[lchild_index];
            min_child_index = lchild_index;
        } else {
            min_child_node = heap->array[rchild_index];
            min_child_index = rchild_index;
        }
    }

    if (heap->array[index]->cost < min_child_node->cost) {
        swap(heap, index, min_child_index);
        siftDown(heap, min_child_index);
    }

}

void decreaseKey(HEAP *heap, int index, int new_cost)
{
    heap->array[index]->cost = new_cost;
    printf("logre definir el costo indice %d\n", index);
    siftUp(heap, index);
}