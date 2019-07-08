typedef struct Buffer {
    long byteLength;
    unsigned char *arrayByffer;
} Buffer;

#ifndef BUFFER_H
#define BUFFER_H

Buffer allocBuffer(int byteLength);
Buffer allocBufferFrom(unsigned char *(array), int arraySize);

Buffer fillBuffer(Buffer buffer, unsigned char byte);

long getByteLength(Buffer buffer);

void readBytes(Buffer buffer, void fn(int byte, long index));
void writeBytes(Buffer buffer, unsigned char *(array), long arraySize);

void writeInt8(Buffer buffer, unsigned char *(value), long offset);
int readInt8(Buffer buffer, long offset);


int readInt8(Buffer buffer, long offset);

short int readInt16(Buffer buffer, long offset);
int readInt32(Buffer buffer, long offset);
long readInt64(Buffer buffer, long offset);

unsigned short int readUInt16(Buffer buffer, long offset);
unsigned int readUInt32(Buffer buffer, long offset);
unsigned long readUInt64(Buffer buffer, long offset);

#endif 