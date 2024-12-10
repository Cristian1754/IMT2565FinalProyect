#pragma once
#include "structures.h"

CONN *connInnit(int to_id, int cost)
{
    CONN *conn = calloc(1, sizeof(CONN));
    conn->to_id = to_id;
    conn->cost = cost;
    return conn;
}

void connFree(CONN *conn)
{
    if (conn != NULL)
    {
        connFree(conn->next_conn);
        free(conn);
    };
}

NODE *nodeInnit(int id)
{
    NODE *node = calloc(1, sizeof(NODE));
    node->id = id;
    node->cost = 0;
    node->conn = NULL;
    node->fnode = NULL;
    node->heap_index = -1;
    node->state = -1;
    return node;
}

void nodeFree(NODE *node)
{
    if (node != NULL)
    {
        connFree(node->conn);
        free(node);
    }
}

void addConn(NODE **node_list, int node1_id, int node2_id, int cost)
{
    NODE *node1 = node_list[node1_id];
    NODE *node2 = node_list[node2_id];

    CONN *conn1 = connInnit(node2_id, cost);
    conn1->next_conn = node1->conn;
    node1->conn = conn1;

    CONN *conn2 = connInnit(node1_id, cost);
    conn2->next_conn = node2->conn;
    node2->conn = conn2;
}

FNODE *fnodeInnit(NODE *key_node)
{
    FNODE *fnode = calloc(1, sizeof(FNODE));
    fnode->key_node = key_node;
    fnode->degree = 0;
    fnode->marked = 0;
    fnode->is_root = 1;
    fnode->parent = NULL;
    fnode->lbro = NULL;
    fnode->rbro = NULL;
    fnode->child = NULL;
    return fnode;
}