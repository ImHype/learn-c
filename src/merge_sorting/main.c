#include "merge_sorting.h"
#include "../toolkit.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
    int arr[] = {5, 1, 2, 3, 4, 5};
    merge_sorting(arr, ARRAY_SIZE(arr));

    assert(arr[0] == 1);
    return 0;
}
