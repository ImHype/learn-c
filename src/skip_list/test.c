#include "skip_list.h"
#include <stdio.h>
#include <assert.h>


int main(int argc, char const *argv[])
{
    skip_list_t skip_list;
    skip_list_t * p = &skip_list;

    init_skip_list(p);

    skip_list_insert(p, 1);
    skip_list_insert(p, 2);

    node_t * tmp = skip_list_find(p, 1);
    assert(tmp && tmp->value == 1);

    skip_list_insert(p, 3);

    tmp = skip_list_find(p, 3);
    assert(tmp && tmp->value == 3);

    tmp = skip_list_find(p, 2);
    assert(tmp && tmp->value == 2);

    skip_list_remove(p, 1);

    tmp = skip_list_find(p, 1);
    assert(tmp == NULL);

    skip_list_remove(p, 2);

    tmp = skip_list_find(p, 2);
    assert(tmp == NULL);
    return 0;
}
