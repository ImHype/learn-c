#include "../heap/heap.h"

int heap_sorting (int arr[], int size) {
    min_heap_t heap;
    min_heap_t * p = &heap;

    init_min_heap(p, size);

    for (int i = 0; i < size; i++)
    {
        p->push(p, arr[i]);
    }

    for (int i = 0; i < size; i++)
    {
        p->pop(p, &arr[i]);
    }

    return 0;
}