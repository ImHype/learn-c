#include "stdlib.h"
#include "string.h"

void quick_sorting(int *a, int left, int right)
{
    if(left >= right)
    {
        return ;
    }
    int i = left;
    int j = right;

    int key = a[left];


    while (i < j)
    {
        while (i < j && a[j] >= key)
        {
            j--;
        }

        a[i] = a[j];

        while (i < j && a[i] <= key)
        {
            i++;
        }
        a[j] = a[i];
    }

    a[i] = key;


    quick_sorting(a, left, i - 1);
    quick_sorting(a, i + 1, right);
}

void quick_sorting_concat(int arr[], int left, int size)
{
    if (size == 0) {
        return;
    }

    if (size == 2) {
        if (arr[0] > arr[1]) {
            int temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        return;
    }

    int center = 0;
    int key = arr[center];

    int little = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < key) {
            little++;
        }
    }

    int large = (size - 1) - little;
    int * left_arr = malloc(sizeof(int) * little);
    int * right_arr = malloc(sizeof(int) * large);

    int little_pos = 0;
    int large_pos = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < key) {
            left_arr[little_pos++] = arr[i];
        } else {
            right_arr[large_pos++] = arr[i];
        }
    }

    quick_sorting_concat(left_arr, 0, little);
    quick_sorting_concat(right_arr, 0, large);
    
    int i = 0;

    while (i < little)
    {
        int left_key = left_arr[i];
        arr[i++] = left_key;
    }
    arr[i++] = key;

    int j = 0;
    while (j < large)
    {
        arr[i++] = right_arr[j++];
    }

    free(left_arr);
    free(right_arr);
}