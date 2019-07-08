#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "buffer.h"


Buffer fillBuffer(Buffer buffer, unsigned char byte) {
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

void writeInt8(Buffer buffer, unsigned char *(value), long offset) {
    assert(offset <= buffer.byteLength - 1);
    buffer.arrayByffer[offset] = *value;
}

int readInt8(Buffer buffer, long offset) {
    return buffer.arrayByffer[offset];
}

short readInt16(Buffer buffer, long offset) {
    return *(short *) (&buffer.arrayByffer[offset]);
}

int readInt32(Buffer buffer, long offset) {
    return *(int *) (&buffer.arrayByffer[offset]);
}

long readInt64(Buffer buffer, long offset) {
    return *(long *) (&buffer.arrayByffer[offset]);
}

unsigned short readUInt16(Buffer buffer, long offset) {
    return *(unsigned short *) (&buffer.arrayByffer[offset]);
}

unsigned int readUInt32(Buffer buffer, long offset) {
    return *(unsigned int *) (&buffer.arrayByffer[offset]);
}

unsigned long readUInt64(Buffer buffer, long offset) {
    return *(unsigned long *) (&buffer.arrayByffer[offset]);
}

void readBytes(Buffer buffer, void (*fn)(int byte, long index)) {
    long byteLength = getByteLength(buffer);
    long i = 0;

    while(i < byteLength) {
        fn(readInt8(buffer, i), i);
        i++;
    }
}

void writeBytes(Buffer buffer, unsigned char *(array), long arraySize) {
    long byteLength = getByteLength(buffer);
    long size = byteLength > size ? byteLength: size;
    long i = 0;

    while(i < size) {
        writeInt8(buffer, &array[i], i);
        i++;
    }
}

Buffer allocBuffer(int byteLength) {
    Buffer buffer;
    buffer.byteLength = byteLength;
    buffer.arrayByffer = (unsigned char *)malloc( byteLength * sizeof(char) );
    fillBuffer(buffer, 0);
    return buffer;
}

Buffer allocBufferFrom(unsigned char *(array), int arraySize) {
    Buffer buffer;
    buffer.byteLength = arraySize;
    buffer.arrayByffer = (unsigned char *)malloc( arraySize * sizeof(char) );

    writeBytes(buffer, array, arraySize);

    return buffer;
}