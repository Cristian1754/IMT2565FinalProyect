#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node; typedef struct node NODE;
struct fnode; typedef struct fnode FNODE;
struct conn; typedef struct conn CONN;

struct conn{
    int to_id;
    int cost;
    CONN* next_conn;
};

CONN* connInnit(int to_id, int cost);
void connFree(CONN* conn);

struct node{
    int id;
    int cost;
    FNODE* fnode;
    CONN* conn;
    int state;
};

NODE* nodeInnit(int id);
void nodeFree(NODE* node);
void addConn(NODE** node_list, int node1_id, int node2_id, int cost);

struct fnode{
    NODE* key_node;
    int degree;
    int marked;
    int is_root;
    FNODE* parent;
    FNODE* lbro;
    FNODE* rbro;
    FNODE* child;
};

FNODE* fnodeInnit(NODE* key_node);