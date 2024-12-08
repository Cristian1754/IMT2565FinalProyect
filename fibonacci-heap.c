#pragma once
#include "fibonacci-heap.h"

FHEAP* fheapInnit(int max_degree) {

    FHEAP* fheap = calloc(1, sizeof(FHEAP));
    fheap->max_degree = max_degree;
    fheap->number_of_roots = 0;
    fheap->min_root = NULL;
    return fheap;
}

void insertFnode(FHEAP* fheap, FNODE* fnode) {

    printf("Inserto el nodo %d con costo %d\n", fnode->key_node->id, fnode->key_node->cost);
    if (fheap->number_of_roots == 0) {
        fheap->min_root = fnode;
        fnode->lbro  = fnode;
        fnode->rbro = fnode;
        fheap->number_of_roots = fheap->number_of_roots + 1;
        fheap->min_root = fnode;
        fnode->is_root = 1;
        printf("\tAhora %d es el nuevo mínimo\n", fnode->key_node->id);
        return;
    }

    fnode->rbro = fheap->min_root;
    fnode->lbro = fheap->min_root->lbro;
    fheap->min_root->lbro->rbro = fnode;
    fheap->min_root->lbro = fnode;

    if (fheap->min_root->key_node->cost > fnode->key_node->cost) {
        fheap->min_root = fnode;
        printf("\tAhora %d es el nuevo mínimo\n", fnode->key_node->id);
    }

    fnode->is_root = 1;
    fheap->number_of_roots = fheap->number_of_roots + 1;
}

void moveToRoot(FHEAP* fheap, FNODE* fnode) {

    printf("Muevo %d a la raiz\n", fnode->key_node->id);
    if (fnode->parent == NULL) { printf("HOLA\n");}
    if (fnode->parent->degree == 1) {
        fnode->parent->child = NULL;
    }
    else {
        fnode->parent->child = fnode->lbro;
        fnode->rbro->lbro = fnode->lbro;
        fnode->lbro->rbro = fnode->rbro;
    }

    fnode->parent->degree = fnode->parent->degree - 1;
    // fnode->parent = NULL;

    insertFnode(fheap, fnode);
}

FNODE* fnodeUnion(FNODE* fnode1, FNODE* fnode2) {

    printf("Uno los fnodos %d y %d\n", fnode1->key_node->id, fnode2->key_node->id);
    FNODE* parent_fnode;
    FNODE* child_fnode;

    if (fnode1->key_node->cost < fnode2->key_node->cost) {
        parent_fnode = fnode1;
        child_fnode = fnode2;
        printf("\t %d sera el padre de %d\n", fnode1->key_node->id, fnode2->key_node->id);
    } else {
        parent_fnode = fnode2;
        child_fnode = fnode1;
        printf("\t %d sera el padre de %d\n", fnode2->key_node->id, fnode1->key_node->id);
    }
    
    if (parent_fnode->child == NULL) {
        parent_fnode->child = child_fnode;
        child_fnode->rbro = child_fnode;
        child_fnode->lbro = child_fnode;
    } else {
        child_fnode->rbro = parent_fnode->child;
        child_fnode->lbro = parent_fnode->child->lbro;
        parent_fnode->child->lbro->rbro = child_fnode;
        parent_fnode->child->lbro = child_fnode;
    }

    child_fnode->parent = parent_fnode;
    child_fnode->is_root = 0;
    parent_fnode->degree = parent_fnode->degree + 1;
    return parent_fnode;
}

NODE* extractMin(FHEAP* fheap) {

    printf("Extraigo el minimo del heap\n");
    if (fheap->number_of_roots == 0) { return NULL;}

    FNODE* fnode = fheap->min_root;
    NODE* node = fnode->key_node;
    int degree = fnode->degree;
    printf("\t %d es el minimo\n", fnode->key_node->id);

    FNODE* current_child = fnode->child;
    FNODE* next_child;
    for (int i = 0; i < degree; i += 1) {
        next_child = current_child->lbro;
        moveToRoot(fheap, current_child);
        current_child->parent = NULL;
        current_child = next_child;
    }

    if (fheap->number_of_roots == 1) {
        fheap->min_root = NULL;
        fheap->number_of_roots = fheap->number_of_roots - 1;
    } else { 
        fheap->min_root = fnode->lbro;
        fnode->lbro->rbro = fnode->rbro;
        fnode->rbro->lbro = fnode->lbro;
        fheap->number_of_roots = fheap->number_of_roots - 1;
        condenseRoots(fheap);
    }

    free(fnode);
    return node;
}

void condenseRoots(FHEAP* fheap) {
    
    printf("Condenso el Heap\n");
    FNODE* buffer[fheap->max_degree];
    for (int i = 0; i < fheap->max_degree; i += 1) { buffer[i] = NULL;}

    FNODE* current_root = fheap->min_root;
    FNODE* next_root;
    for (int i = 0; i < fheap->number_of_roots; i += 1) {
        next_root = current_root->lbro;
        insertInBuffer(buffer, current_root);
        current_root = next_root;
    }

    fheap->number_of_roots = 0;
    fheap->min_root = NULL;
    for (int i = 0; i < fheap->max_degree; i += 1) {
        if (buffer[i] != NULL) {
            insertFnode(fheap, buffer[i]);
        }
    }
}

void insertInBuffer(FNODE* buffer[], FNODE* fnode) {

    printf("Quiero insertar nodo %d con grado %d al buffer\n", fnode->key_node->id, fnode->degree);
    if (buffer[fnode->degree] == NULL) {
        printf("\t Se ha insertado con exito\n");
        buffer[fnode->degree] = fnode;
        return;
    }
    printf("\t No es posible la inserción\n");

    FNODE* fnode2 = buffer[fnode->degree];
    buffer[fnode->degree] = NULL;
    FNODE* new_fnode = fnodeUnion(fnode, fnode2);
    insertInBuffer(buffer, new_fnode);
}

void cutOutFnode(FHEAP* fheap, FNODE* fnode) {

    printf("Corto el nodo %d\n", fnode->key_node->id);
    if (fnode->is_root == 1) { return;}

    moveToRoot(fheap, fnode);
    fnode->marked = 0;
    printf("\t Nodo %d ya no esta marcado\n", fnode->key_node->id);

    if (fnode->parent == NULL) {printf("HOLA\n");}
    if (fnode->parent->marked == 0) {
        fnode->parent->marked = 1;
        printf("\t El padre del nodo %d, %d esta marcado\n", fnode->key_node->id, fnode->parent->key_node->id);
    } else {
        cutOutFnode(fheap, fnode->parent);
    }
    fnode->parent = NULL;
}

void decreaseKey(FHEAP* fheap, NODE* key_node, int new_cost) {

    key_node->cost = new_cost;
    FNODE* fnode = key_node->fnode;
    printf("El nuevo valor de %d ahora es %d\n", fnode->key_node->id, new_cost);
    
    if (fnode->is_root == 1) {
        if (new_cost < fheap->min_root->key_node->cost) {
            fheap->min_root = fnode;
        }
        return;
    }
    printf("el nodo %d tien costo %d, su padre %d tiene costo %d\n",
    fnode->key_node->id, fnode->key_node->cost, fnode->parent->key_node->id,
    fnode->parent->key_node->cost);
    if (new_cost < fnode->parent->key_node->cost) {
        // printf("HOLA\n");
        cutOutFnode(fheap, fnode);
    }
}