#include "quick_sorting.h"
#include "../toolkit.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
    int arr[] = { 5, 4, 3, 2, 1};
    int arr2[] = { 5, 4, 3, 2};
    int arr3[] = { 1, 2, 3, 4, 6, 1};
    quick_sorting(arr, 0, ARRAY_SIZE(arr) - 1);
    quick_sorting_concat(arr2, 0, ARRAY_SIZE(arr2));
    quick_sorting_concat(arr3, 0, ARRAY_SIZE(arr3));
    assert(arr[0] == 1);
    assert(arr2[0] == 2);
    assert(arr3[0] == 1);
    assert(arr3[1] == 1);
    return 0;
}
