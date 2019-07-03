#include"stdio.h"
#include <string.h>

struct FixedLengthArrayBuffer
{
    char data[50];
    int size;
};

void printBufferArray();
void printBufferArray(struct FixedLengthArrayBuffer buffer);

void printBufferArray(struct FixedLengthArrayBuffer buffer) {
    printf("Buffer size: %d\n", buffer.size);
    printf("Buffer data: %s\n", buffer.data);
}

void ArrayVersion() {
    struct FixedLengthArrayBuffer buffer1;

    /** initial **/
    buffer1.size = 5;
    strcpy(buffer1.data, "12345");

    /** print **/
    printBufferArray(buffer1);
}

