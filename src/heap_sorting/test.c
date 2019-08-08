#include "heap_sorting.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])


int main(int argc, char const *argv[])
{
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = ARRAY_SIZE(arr);
    int space = size * sizeof(int);
    int * tmp = malloc(space);

    memcpy(tmp, arr, space);
    heap_sorting(arr, size);

    for (int i = 0; i < size; i++)
    {
        assert(arr[i] == tmp[size - 1 - i]);
    }

    return 0;
}
