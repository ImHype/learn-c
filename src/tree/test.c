#include "tree.h"
#include "assert.h"

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

    return 0;
}
