#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node; typedef struct node NODE;
struct hnode; typedef struct hnode HNODE;
struct conn; typedef struct conn CONN;
struct fiboheap; typedef struct fiboheap FIBOHEAP;

struct conn{
    int to_id;
    int cost;
    CONN* next_conn;
};

CONN* connInnit(int to_id, int cost);
void connFree(CONN* conn);

struct node{
    int id;
    HNODE* hnode;
    CONN* conn;
};

NODE* nodeInnit(int id);
void nodeFree(NODE* node);
void addConn(NODE** node_list, int node1_id, int node2_id, int cost);

struct hnode{
    NODE* key_node;
    int rank;
    int lost;
    HNODE* father;
    HNODE* left_brother;
    HNODE* right_brother;
    HNODE* son;
};

HNODE* hnodeInnit(NODE* key_node);

struct fiboheap{
    HNODE* min_root;
};