#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Buffer
{
    long size;
    char *data;
};


struct Buffer initBuffer(int *(array)) {
    struct Buffer buffer;
    buffer.size = sizeof(array);
    
    char *data = (char *)malloc( 200 * sizeof(char) );

    strcpy(data, "Zara ali a DPS student.");

    buffer.data = data;

    return buffer;
}

void printBuffer(struct Buffer buffer)
{
    printf("size: %lu", buffer.size);
    printf("size: %s", buffer.data);
};


int main()
{
    int size;
    int *data;
    struct Buffer buffer;

    int data2[5] = {1, 2, 3, 4, 5};

    size = 100;

    buffer = initBuffer(data2);

    printBuffer(buffer);
}