#include <stdio.h>
#include <string.h>
#include "show_bytes.h"

int is_little_endian(void)
{
    int test = 0xff;
    byte_pointer p = (byte_pointer)&test;
    return p[0] ? 1 : 0;
}

void show_bytes(byte_pointer start, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (is_little_endian())
        {
            printf(" %.2x", start[len - 1 - i]);
        }
        else
        {
            printf(" %.2x", start[i]);
        }
    }
    printf("\n");
}

void show_binary(byte_pointer start, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf(" ");
        if (is_little_endian())
        {
            for (size_t j = 8; j > 0; j--)
            {
                printf("%d", (start[len - 1 - i] >> (j - 1)) & 1);
            }
        }
        else
        {
            for (size_t j = 8; j > 0; j--)
            {
                printf("%d", (start[i] >> (j - 1)) & 1);
            }
        }
    }
    printf("\n");
}

void show_short(short x, Mode mode)
{
    switch (mode)
    {
    case HEX:
        show_bytes((byte_pointer)&x, sizeof(short));
        break;
    case BIN:
        show_binary((byte_pointer)&x, sizeof(short));
        break;
    }
}

void show_int(int x, Mode mode)
{
    switch (mode)
    {
    case HEX:
        show_bytes((byte_pointer)&x, sizeof(int));
        break;
    case BIN:
        show_binary((byte_pointer)&x, sizeof(int));
        break;
    }
}

void show_long(long x, Mode mode)
{
    switch (mode)
    {
    case HEX:
        show_bytes((byte_pointer)&x, sizeof(long));
        break;
    case BIN:
        show_binary((byte_pointer)&x, sizeof(long));
        break;
    }
}

void show_float(float x, Mode mode)
{
    switch (mode)
    {
    case HEX:
        show_bytes((byte_pointer)&x, sizeof(float));
        break;
    case BIN:
        show_binary((byte_pointer)&x, sizeof(float));
        break;
    }
}

void show_double(double x, Mode mode)
{
    switch (mode)
    {
    case HEX:
        show_bytes((byte_pointer)&x, sizeof(double));
        break;
    case BIN:
        show_binary((byte_pointer)&x, sizeof(double));
        break;
    }
}

void show_pointer(void* x, Mode mode)
{
    switch (mode)
    {
    case HEX:
        show_bytes((byte_pointer)&x, sizeof(void*));
        break;
    case BIN:
        show_binary((byte_pointer)&x, sizeof(void*));
        break;
    }
}