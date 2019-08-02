#include "heap.h"
#include <stdio.h>

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])
int main(int argc, char const *argv[])
{
    min_heap_t heap;
    min_heap_t * h = &heap;

    init_min_heap(h, 1024);

    int arr[] = {1,2,3,4,5,6,7,8,9,10,100, -1, -2,-3};

    for (int i = 0; i < ARRAY_SIZE(arr); i++)
    {

        h->push(h, arr[i]);
    }

    for (int i = 0; i < ARRAY_SIZE(arr); i++)
    {
        int pop_num;
        h->pop(h, &pop_num);

        printf("%d\n", pop_num);
    }

    return 0;
}
