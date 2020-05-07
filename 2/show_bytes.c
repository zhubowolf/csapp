#include <stdio.h>
#include <string.h>
#include "show_bytes.h"

void show_bytes(byte_pointer start, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_binary(byte_pointer start, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf(" ");
        for (size_t j = 8; j > 0; j--)
        {
            printf("%d", (start[i] >> (j - 1)) & 1);
        }
    }
    printf("\n");
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