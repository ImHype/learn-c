#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "buffer.h"

char nilByte = 0;
char nilBytes[] = {};


Buffer bufferAlloc(int byteLength);


Buffer fillBuffer(Buffer buffer, char byte) {
    long byteLength = getByteLength(buffer);
    long i = 0;
    while(i < byteLength) {
        writeInt8(buffer, &byte, i);
        i++;
    }
    return buffer;
}

long getByteLength(Buffer buffer) {
    return buffer.byteLength;
}

void writeInt8(Buffer buffer, char *(value), long offset) {
    assert(offset <= buffer.byteLength - 1);
    buffer.arrayByffer[offset] = *value;
}

int readInt8(Buffer buffer, long offset) {
    return buffer.arrayByffer[offset];
}

void readEachByte(Buffer buffer, void fn(int byte, long index)) {
    long byteLength = getByteLength(buffer);
    long i = 0;

    while(i < byteLength) {
        fn(readInt8(buffer, i), i);
        i++;
    }
}

void writeEachByte(Buffer buffer, char *(array), long arraySize) {
    long byteLength = getByteLength(buffer);
    long size = byteLength > size ? byteLength: size;
    long i = 0;

    while(i < size) {
        char byte = array[i];
        writeInt8(buffer, &byte, i);
        i++;
    }
}

Buffer allocBuffer(int byteLength) {
    Buffer buffer;
    buffer.byteLength = byteLength;
    buffer.arrayByffer = (char *)malloc( byteLength * sizeof(char) );
    fillBuffer(buffer, 0);
    return buffer;
}

Buffer allocBufferFrom(char *(array), int arraySize) {
    Buffer buffer;
    buffer.byteLength = arraySize;
    buffer.arrayByffer = (char *)malloc( arraySize * sizeof(char) );

    writeEachByte(buffer, array, arraySize);

    return buffer;
}