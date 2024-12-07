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

    if (fheap->number_of_roots = 0) {
        fheap->min_root = fnode;
        fnode->lbro  = fnode;
        fnode->rbro = fnode;
        return;
    }

    fnode->rbro = fheap->min_root;
    fnode->lbro = fheap->min_root->lbro;
    fheap->min_root->lbro->rbro = fnode;
    fheap->min_root->lbro = fnode;

    if (fheap->min_root->key_node->cost > fnode->key_node->cost) {
        fheap->min_root = fnode;
    }

    fnode->is_root = 1;
    fheap->number_of_roots = fheap->number_of_roots + 1;
}

void moveToRoot(FHEAP* fheap, FNODE* fnode) {

    if (fnode->parent->degree == 1) {
        fnode->parent->child = NULL;
    }
    else {
        fnode->parent->child = fnode->lbro;
        fnode->rbro->lbro = fnode->lbro;
        fnode->lbro->rbro = fnode->rbro;
    }

    fnode->parent->degree = fnode->parent->degree - 1;
    fnode->parent = NULL;

    insertFnode(fheap, fnode);
}

FNODE* fnodeUnion(FNODE* fnode1, FNODE* fnode2) {

    FNODE* parent_fnode;
    FNODE* child_fnode;

    if (fnode1->key_node->cost < fnode2->key_node->cost) {
        parent_fnode = fnode1;
        child_fnode = fnode2;
    } else {
        parent_fnode = fnode2;
        child_fnode = fnode1;
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

void cutOutFnode(FHEAP* fheap, FNODE* fnode) {

    if (fnode->is_root == 1) { return;}

    moveToRoot(fheap, fnode);
    fnode->marked = 0;
    if (fnode->parent->marked == 0) {
        fnode->parent->marked = 1;
    } else {
        cutOutFnode(fheap, fnode->parent);
    }
}

void decreaseKey(FHEAP* fheap, NODE* key_node, int new_cost) {

    key_node->cost = new_cost;
    FNODE* fnode = key_node->fnode;

    if (fnode->is_root == 1) {
        if (new_cost < fheap->min_root->key_node->cost) {
            fheap->min_root = fnode;
        }
        return;
    }

    if (new_cost < fnode->parent->key_node->cost) {
        cutOutFnode(fheap, fnode);
    }
}

NODE* extractMin(FHEAP* fheap) {

    if (fheap->number_of_roots == 0) { return NULL;}

    FNODE* fnode = fheap->min_root;
    NODE* node = fnode->key_node;

    FNODE* current_child = fnode->child;
    for (int i = 0; i < fnode->degree; i += 1) {
        moveToRoot(fheap, current_child);
        current_child = fnode->child;
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
    
    FNODE* buffer[fheap->max_degree];
    for (int i = 0; i < fheap->max_degree; i += 1) { buffer[i] = NULL;}

    FNODE* current_root = fheap->min_root;
    for (int i = 0; i < fheap->number_of_roots; i += 1) {
        insertInBuffer(buffer, current_root);
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
    if (buffer[fnode->degree] == NULL) {
        buffer[fnode->degree] = fnode;
        return;
    }

    FNODE* fnode2 = buffer[fnode->degree];
    FNODE* new_fnode = fnodeUnion(fnode, fnode2);
    buffer[fnode->degree] = NULL;
    insertInBuffer(buffer, new_fnode);
}