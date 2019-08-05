int swap (int * a, int * b) {
    if (*a > *b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }

    return 0;
}

int selection_sorting(int arr[], int size) {
    for (int i = 0; i < size; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        swap(&arr[i], &arr[min]);
    }
       
    return 0;
}