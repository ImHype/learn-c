int bubble_sorting(int * arr, int size) {
    int is_change = 1;

    while (is_change) {
        is_change = 0;
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                is_change = 1;
            }
        }
    }
    return 0;
}