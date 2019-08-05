#include "skip_list.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char const *argv[])
{
    skip_list_t skip_list;
    skip_list_t * p = &skip_list;

    init_skip_list(p);

    p->insert(p, 1);
    p->insert(p, 2);

    node_t * tmp = p->find(p, 1);
    assert(tmp && tmp->value == 1);

    p->insert(p, 3);

    tmp = p->find(p, 3);
    assert(tmp && tmp->value == 3);

    tmp = p->find(p, 2);
    assert(tmp && tmp->value == 2);

    p->remove(p, 1);

    tmp = p->find(p, 1);
    assert(tmp == NULL);

    p->remove(p, 2);

    tmp = p->find(p, 2);
    assert(tmp == NULL);
    return 0;
}
