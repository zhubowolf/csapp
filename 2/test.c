#include "show_bytes.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

void test_show_bytes(int val)
{
    printf("test show bytes\n");
    int iVal = val;
    float fVal = (float)iVal;
    int *pVal = &iVal;
    short s = 12345;
    long l = 123456789;
    float f = 1.0;
    double d = 1.0;
    show_int(iVal, HEX);
    show_float(fVal, HEX);
    show_pointer(pVal, HEX);
    show_short(s, HEX);
    show_long(l, HEX);
    show_float(f, BIN);
    show_double(d, BIN);
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
    printf("test 2.25\n");
    float a[] = {0};
    printf("%f\n", sum_elements(a, 0));
}

// Determine whether string s is longer than string t
int strlonger(char * s, char * t)
{
    // return strlen(s) - strlen(t) > 0;// bug
    return strlen(s) > strlen(t);
}

void test2_26(void)
{
    printf("test 2.26\n");
    char *s = "12345";
    char *t = "1234567";
    printf("%s longer than %s:%s\n", s, t, strlonger(s, t) ? "true" : "false");
}

// Determine whether arguments can be added without overflow
int uadd_ok(unsigned x, unsigned y)
{
    return (x + y) > x | (x + y) > y;
}

void test2_27(void)
{
    printf("test 2.27\n");
    unsigned x = 0xffffffff;
    unsigned y = 1;
    unsigned x1 = 0xffffffff;
    unsigned y1 = 0;
    printf("%x + %x is overflow:%s\n", x, y, uadd_ok(x, y) ? "false" : "true");
    printf("%x + %x is overflow:%s\n", x1, y1, uadd_ok(x1, y1) ? "false" : "true");
}

// Determine whether arguments can be added without overflow
int tadd_ok(int x, int y)
{
    int sum = x + y;
    int neg_over = x < 0 && y < 0 && sum >= 0;
    int pos_over = x >= 0 && y >= 0 && sum < 0;
    return !neg_over && !pos_over;
}

void test2_30(void)
{
    printf("test 2.30\n");
    int a = INT_MAX, b = INT_MAX;
    int c = INT_MIN, d = INT_MIN;
    int e = 0x76543210, f = 0x87654321;
    printf("%d + %d = %d %s\n", a, b, a + b, tadd_ok(a, b) ? "normal" : "overflow");
    printf("%d + %d = %d %s\n", c, d, c + d, tadd_ok(c, d) ? "normal" : "overflow");
    printf("%d + %d = %d %s\n", e, f, e + f, tadd_ok(e, f) ? "normal" : "overflow");
}

// Determine whether arguments can be subtracted without overflow
int tsub_ok(int x, int y)
{
    // return tadd_ok(x, -y);//buggy
    if (y > INT_MIN)
    {
        return tadd_ok(x, -y);
    }
    else
    {
        return 1;
    }
}

void test2_32(void)
{
    printf("test 2.32\n");
    int a = INT_MAX, b = INT_MAX;
    int c = -1, d = INT_MIN;
    int e = 0x76543210, f = 0x87654321;
    printf("%d - %d = %d %s\n", a, b, a - b, tsub_ok(a, b) ? "normal" : "overflow");
    printf("%d - %d = %d %s\n", c, d, c - d, tsub_ok(c, d) ? "normal" : "overflow");
    printf("%d - %d = %d %s\n", e, f, e - f, tsub_ok(e, f) ? "normal" : "overflow");
}

int tmult_ok(int x, int y)
{
    // int p = x * y; //buggy
    // return !x || p / x == y;

    int64_t p = (int64_t)x * y;
    return p == (int)p;
}

void test2_36(void)
{
    printf("test 2.36\n");
    int a = INT_MAX, b = INT_MAX;
    int c = -1, d = INT_MIN;
    int e = 0x76543210, f = 0x87654321;
    printf("%d * %d = %d %s\n", a, b, (int)(a * b), tmult_ok(a, b) ? "normal" : "overflow");
    printf("%d * %d = %d %s\n", c, d, (int)(c * d), tmult_ok(c, d) ? "normal" : "overflow");
    printf("%d * %d = %d %s\n", e, f, (int)(e * f), tmult_ok(e, f) ? "normal" : "overflow");
}

//XDR vulnerability
void* copy_elements(void * ele_src[], int ele_cnt, size_t ele_size)
{
    if (!tmult_ok(ele_cnt, ele_size))
    {
        return NULL;
    }

    void *result = malloc(ele_cnt * ele_size);
    if (result == NULL)
    {
        return NULL;
    }
    void *next = result;
    for (size_t i = 0; i < ele_cnt; i++)
    {
        memcpy(next, ele_src[i], ele_size);
        next += ele_size;
    }
    return result;
}

void test_XDR_vulnerability(void)
{
    char * array[1] = {NULL};
    array[0] = "xdr vulnerability";
    char *p = (char *)copy_elements((void**)array, 1048577, 4096);
    if (p)
    {
        printf("%s\n", (char*)p);
        return;
    }
    printf("copy elements failed!\n");
    p = (char *)copy_elements((void**)array, 10, 4096);
    if (p)
    {
        printf("%s\n", (char*)p);
        return;
    }
    printf("copy elements failed!\n");
}

int div16(int x)
{
    int bias = (x >> 31) & 0xf;
    return (x + bias) >> 4;
}

void test2_42(void)
{
    printf("test 2.42\n");
    printf("256 / 16 = %d\n", div16(256));
    printf("-256 / 16 = %d\n", div16(-256));
    printf("%d / 16 = %d\n", INT_MAX, div16(INT_MAX));
    printf("%d / 16 = %d\n", INT_MIN, div16(INT_MIN));
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
    test2_30();
    int a = INT_MIN;
    int b = INT_MIN + 1;
    // int c = -1 * INT_MIN;   // warning
    // int d = -1 * a; //no warning
    printf("a=%d, -a=%d\n", a, -a);
    printf("b=%d, -b=%d\n", b, -b);
    test2_32();
    test2_36();
    // test_XDR_vulnerability();
    test2_42();
    return 0;
}