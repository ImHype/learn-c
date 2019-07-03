typedef struct Buffer {
    long byteLength;
    char *arrayByffer;
} Buffer;

#ifndef BUFFER_H
#define BUFFER_H

Buffer allocBuffer(int byteLength);
Buffer allocBufferFrom(char *(array), int arraySize);

Buffer fillBuffer(Buffer buffer, char byte);

long getByteLength(Buffer buffer);

void readBytes(Buffer buffer, void fn(int byte, long index));
void writeBytes(Buffer buffer, char *(array), long arraySize);

void writeInt8(Buffer buffer, char *(value), long offset);
int readInt8(Buffer buffer, long offset);

#endif 