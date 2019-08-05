#include "bubble_sorting.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
    int arr[] = {5, 4, 3, 2, 1};
    int space = 5 * sizeof(int);
    int * tmp = malloc(space);

    memcpy(tmp, arr, space);
    int size = ARRAY_SIZE(arr);
    bubble_sorting(arr, size);

    for (int i = 0; i < size; i++)
    {
        assert(arr[i] == tmp[size - 1 - i]);
    }
    
    return 0;
}
