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

short int readInt16(Buffer buffer, long offset) {
    short int* num = (short int *) (&buffer.arrayByffer[offset]);
    return *num;
}

short int readInt32(Buffer buffer, long offset) {
    int* num = (int *) (&buffer.arrayByffer[offset]);
    return *num;
}

short int readInt64(Buffer buffer, long offset) {
    long int* num = (long int *) (&buffer.arrayByffer[offset]);
    return *num;
}

short int readUInt16(Buffer buffer, long offset) {
    unsigned short int* num = (unsigned short int *) (&buffer.arrayByffer[offset]);
    return *num;
}

short int readUInt32(Buffer buffer, long offset) {
    unsigned int* num = (unsigned int *) (&buffer.arrayByffer[offset]);
    return *num;
}

short int readUInt64(Buffer buffer, long offset) {
    unsigned long int* num = (unsigned long int *) (&buffer.arrayByffer[offset]);
    return *num;
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