#include "show_bytes.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

void test_show_bytes(int val)
{
    printf("test show bytes\n");
    int iVal = val;
    float fVal = (float)iVal;
    int *pVal = &iVal;
    show_int(iVal, HEX);
    show_float(fVal, HEX);
    show_pointer(pVal, HEX);
}

void test2_5(void)
{
    printf("test 2.5\n");
    int val = 0x87654321;
    byte_pointer p = (byte_pointer)&val;
    show_bytes(p, 1);
    show_bytes(p, 2);
    show_bytes(p, 3);
}

void test2_6(void)
{
    printf("test 2.6\n");
    int num = 3510593;
    float fnum = 3510593.0;
    show_int(num, HEX);
    show_int(num, BIN);
    show_float(fnum, HEX);
    show_float(fnum, BIN);
}

void test2_7(void)
{
    printf("test 2.7\n");
    const char *s = "abcdef";
    show_bytes((byte_pointer)s, strlen(s));
}

void inplace_swap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void test2_10(void)
{
    printf("test 2.10\n");
    int x = 0x12345678;
    int y = 0x87654321;
    show_int(x, HEX);
    show_int(y, HEX);
    inplace_swap(&x, &y);
    show_int(x, HEX);
    show_int(y, HEX);
}

void reverse_array(int a[], size_t cnt)
{
    for (size_t first = 0, last = cnt - 1; first < last; first++, last--)
    {
        inplace_swap(&a[first], &a[last]);
    }
}

void test2_11(void)
{
    printf("test 2.11\n");
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); i++)
    {
        show_int(a[i], HEX);
    }
    reverse_array(a, sizeof(a) / sizeof(a[0]));
    for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); i++)
    {
        show_int(a[i], HEX);
    }
}

void test2_12(void)
{
    printf("test 2.12\n");
    int x = 0x87654321;
    show_int(x & 0xff, HEX);
    show_int(x & 0xff, BIN);
    show_int((~x) ^ 0xff, HEX);
    show_int((~x) ^ 0xff, BIN);
    show_int(x | 0xff, HEX);
    show_int(x | 0xff, BIN);
}

int equal(int x, int y)
{
    return !(x ^ y);
    // return !(x & (~y));
}

void test2_15(void)
{
    printf("test 2.15\n");
    printf("%s\n", equal(26, 26) ? "true" : "false");
    printf("%s\n", equal(26, 0) ? "true" : "false");
}

float sum_elements(float a[], unsigned length)
{
    float result = 0;
    // for (int i = 0; i <= length - 1; i++) // bug
    for (int i = 0; i < length; i++)
    {
        result += a[i];
    }
    return result;
}

void test2_25(void)
{
    float a[] = {0};
    printf("%f\n", sum_elements(a, 0));
}

int strlonger(char * s, char * t)
{
    // return strlen(s) - strlen(t) > 0;// bug
    return strlen(s) > strlen(t);
}

void test2_26(void)
{
    char *s = "12345";
    char *t = "1234567";
    printf("%s longer than %s:%s\n", s, t, strlonger(s, t) ? "true" : "false");
}

int uadd_ok(unsigned x, unsigned y)
{
    return (x + y) >= x;
}

void test2_27(void)
{
    unsigned x = 0xffffffff;
    unsigned y = 1;
    unsigned x1 = 0xffffffff;
    unsigned y1 = 0;
    printf("%x + %x is overflow:%s\n", x, y, uadd_ok(x, y) ? "false" : "true");
    printf("%x + %x is overflow:%s\n", x1, y1, uadd_ok(x1, y1) ? "false" : "true");
}

int main(void)
{
    test_show_bytes(26);
    test2_5();
    test2_6();
    test2_7();
    test2_10();
    test2_11();
    test2_12();
    test2_15();
    test2_25();
    test2_26();
    test2_27();
    return 0;
}