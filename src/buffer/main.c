#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "buffer.h"

void println() {
    printf("\n");
}

void printByte(int byte, long index) {
    printf("{ index: %lu, byte: %d }\n", index, byte);
}

void printBuffer(Buffer buffer) {
    readBytes(buffer, &printByte);
}

int main()
{
    Buffer buffer = allocBuffer(10);
    unsigned char hello = 0x1;
    printf("%d", (int) hello);

    unsigned char val[10] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    Buffer fromArrayedBuffer = allocBufferFrom(val, 10);

    printf("byteLength: %lu", getByteLength(buffer));
    println();
    println();

    printf("initialed buffer:");
    println();

    printBuffer(buffer);
    
    writeInt8(buffer, &val[0], 0);
    writeInt8(buffer, &val[1], 1);
    writeInt8(buffer, &val[2], 2);
    writeInt8(buffer, &val[3], 3);

    println();
    printf("after writeInt8:");
    println();

    printBuffer(buffer);

    println();

    printf("BufferFromArray:");
    println();
    printBuffer(fromArrayedBuffer);
}