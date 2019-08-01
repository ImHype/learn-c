#include <stdlib.h>
#include "heap.h"

node_t * init_node(int value) {
    node_t * node = malloc(sizeof(node_t));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
};

int insert_node(node_t ** nodep, node_t * insert_node) {
    node_t * node = *nodep;

    if (node == NULL) {
        *nodep = insert_node;
        return 0;
    }

    
    
    node->data = value;
};

int insert_heap(heap_t * heap, int value) {
    node_t * node = heap->root;
    node_t * n = init_node(value);
    insert_node(&node, n);
    return 0;
};

int del_heap(heap_t * heap, int value){
    return 0;
};

int init_heap(heap_t * heap) {
    heap->root = NULL;
    heap->insert = insert_heap;
    heap->del = del_heap;

    return 0;
};
