#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "buffer.h"

void println() {
    printf("\n");
}

void printByte(int byte, long index) {
    printf("0x%x ", byte);
}

void printBuffer(Buffer buffer) {
    readBytes(buffer, &printByte);
    println();
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

    printf("init buffer from char array:");
    println();
    printBuffer(fromArrayedBuffer);

    printf("init buffer from string:");
    println();

    Buffer buf = allocBufferFrom((unsigned char*) "hello_world", 11);
    printBuffer(buf);
}