#include "top-k.h"
#include "../heap/heap.h"

int topk(int arr[], int size, int ret_arr[], int ret_size) {
    min_heap_t min_heap;
    min_heap_t * p = &min_heap;

    init_min_heap(p, ret_size);

    for (int i = 0; i < size; i++)
    {
        p->push(p, arr[i]);
    }

    for (int i = 0; i < ret_size; i++)
    {
        p->pop(p, &ret_arr[i]);
    }
    
    return 0;
}