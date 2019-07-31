#include "tree.h"
#include "stdlib.h"

node_t * node_init(int value) {
    node_t * node = malloc(sizeof(node_t));

    node->left = NULL;
    node->right = NULL;
    node->value = value;

    return node;
};

node_t * node_search(node_t ** tree, int value) {
    node_t * p = *tree;

    if (p == NULL) {
        return NULL;
    }

    if (p->value == value) {
        return p;
    }

    if (value < p->value) {
        return node_search(&p->left, value);
    }

    return node_search(&p->right, value);
};

int node_visit(node_t ** tree, int (*callback)(node_t * node)) {
    node_t * p = *tree;

    if (p == NULL) {
        return 0;
    }

    node_visit(&p->left, callback);

    callback(p);

    node_visit(&p->right, callback);

    return 0;
};


int node_add_node(node_t ** tree, node_t * node) {
    node_t * p = *tree;
    if (p == NULL) {
        *tree = node;
        return 0;
    }

    if (node->value < p->value) {
        return node_add_node(&p->left, node);
    }

    return node_add_node(&p->right, node);
};

int tree_init(tree_t * tree) {
    tree->root = NULL;
    return 0;
}

node_t * tree_search(tree_t * tree, int value) {
    return node_search(&tree->root, value);
};

int tree_visit(tree_t * tree, int (*callback)(node_t * node)) {
    return node_visit(&tree->root, callback);
};

int tree_add_node(tree_t * tree, int value) {
    return node_add_node(&tree->root, node_init(value));;
};
