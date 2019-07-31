#include <stdio.h>
#include "tree.h"
#include "assert.h"


int print_node(node_t * node) {
    printf("%d\n", node->value);
    return 0;
}

int main(int argc, char const *argv[])
{
    tree_t tree;

    tree_t * p = &tree;

    tree_init(p);
    
    tree_add_node(p, 0);

    assert(p->root->value == 0);
    tree_add_node(p, 1);
    assert(p->root->right->value == 1);
    tree_add_node(p, -1);
    assert(p->root->left->value == -1);
    tree_add_node(p, 2);
    tree_add_node(p, 3);
    tree_add_node(p, 4);
    tree_add_node(p, 5);
    tree_add_node(p, -3);
    tree_add_node(p, -5);

    tree_visit(p, print_node);

    return 0;
}
