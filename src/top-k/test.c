#include "top-k.h"
#include "assert.h"
#include "stdio.h"
#include "../toolkit.h"

int main(int argc, char const *argv[])
{
    int arr[] = {1,2,3,4,5,6,7};
    int size = ARRAY_SIZE(arr);
    int arr2[3];
    topk(arr, size, arr2, ARRAY_SIZE(arr2));

    assert(arr2[0] == 1);
    assert(arr2[1] == 2);
    
    return 0;
}
