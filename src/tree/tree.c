#include "tree.h"
#include "stdlib.h"

node_t * node_init(int value) {
    node_t * node = malloc(sizeof(node_t));

    node->left = NULL;
    node->right = NULL;
    node->value = value;

    return node;
};

node_t * node_search(node_t * tree, int value) {
    if (tree->value == value) {
        return tree;
    }

    if (value < tree->value && tree->left != NULL) {
        return node_search(tree->left, value);
    }

    if (value > tree->value && tree->right != NULL) {
        return node_search(tree->right, value);
    }

    return NULL;
};

int node_visit(node_t * tree, int (*callback)(node_t * node)) {
    callback(tree);


    if (tree->left != NULL) {
        return node_visit(tree->left, callback);
    }

    if (tree->right != NULL) {
        return node_visit(tree->right, callback);
    }

    return 0;
};

int node_add_node(node_t * tree, node_t * node) {
    if (node->value < tree->value) {
        if (tree->left == NULL) {
            tree->left = node;
        } else {
            node_add_node(tree->left, node);
        }
    } else {
        if (tree->right == NULL) {
            tree->right = node;
        } else {
            node_add_node(tree->right, node);
        }
    }
    return 0;
};

int tree_init(tree_t * tree) {
    tree->root = NULL;
    return 0;
}

node_t * tree_search(tree_t * tree, int value) {
    if (tree->root == NULL) {
        return NULL;
    }

    return node_search(tree->root, value);
};

int tree_visit(tree_t * tree, int (*callback)(node_t * node)) {
    if (tree->root == NULL) {
        return 0;
    } else {
        return node_visit(tree->root, int (*callback)(node_t * node));
    }
};

int tree_add_node(tree_t * tree, int value) {
    node_t * node = node_init(value);

    if (tree->root == NULL) {
        tree->root = node;
    } else {
        node_add_node(tree->root, node);
    }

    return 0;
};
