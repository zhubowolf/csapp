#ifndef SHOW_BYTES_H
#define SHOW_BYTES_H

typedef unsigned char * byte_pointer;
typedef enum mode
{
    HEX = 0,
    BIN = 1
} Mode;

void show_bytes(byte_pointer start, int len);
void show_binary(byte_pointer start, int len);
void show_int(int x, Mode mode);
void show_float(float x, Mode mode);
void show_pointer(void *x, Mode mode);

#endif /* SHOW_BYTES_H */