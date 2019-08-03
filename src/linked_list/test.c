#include "linked-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])


int callback(int index, void * element) {
    printf("%d - %d\n", index, *((int *) element));
    return 0;
}

int main(int argc, char const *argv[])
{
    linked_list_t * linked_list = malloc(sizeof(linked_list_t));

    create_linked_list(linked_list);
    
    int size = linked_list_size(linked_list);

    assert(size == 0);

    assert(linked_list_head(linked_list) == NULL);

    int arr[] = { 1, 2, 3};

    linked_list_add(linked_list, (void *)(&arr[0]));

    node_t * tmp = linked_list_head(linked_list);

    assert(tmp != NULL);

    int index0 = linked_list_index_of(linked_list, tmp->element);

    int index = linked_list_remove(linked_list, tmp->element);

    assert(index0 == index);

    assert(index > -1);

    assert(linked_list_head(linked_list) == NULL);

    assert(linked_list_is_empty(linked_list) == 1);

    linked_list_add(linked_list, (void *)(&arr[1]));

    assert((linked_list_element_at(linked_list, 0)->element) == &arr[1]);
    assert(*((int *) linked_list_element_at(linked_list, 0)->element) == arr[1]);

    linked_list_add_at(linked_list, 0, (void *)(&arr[2]));

    assert(*((int *) (linked_list_head(linked_list))->element) == arr[2]);

    linked_list_remove_at(linked_list, 0);

    assert(linked_list_head(linked_list) == NULL);

    for (int i = 0; i < ARRAY_SIZE(arr); i++)
    {
        linked_list_add(linked_list, &arr[i]);
    }

    linked_list_foreach(linked_list, &callback);

    return 0;
}
