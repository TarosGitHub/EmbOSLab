#include "defines.h"
#include "serial.h"
#include "lib.h"

#define PUTXVAL_BUF_SIZE 9

void* memset(void* s, int c, size_t n)
{
    char *p;

    for (p = s; 0 < n; n--) {
        *p = c;
        p++;
    }

    return s;
}

void* memcpy(void* dst, const void* src, size_t n)
{
    char* d = dst;
    const char* s = src;

    for (; 0 < n; n--) {
        *d = *s;
        d++;
        s++;
    }

    return dst;
}

int memcmp(const void* s1, const void* s2, size_t n)
{
    const char* p1 = s1;
    const char* p2 = s2;

    for (; 0 < n; n--) {
        if (*p1 != *p2) {
            return (*p1 > *p2) ? 1 : -1;
        }
        p1++;
        p2++;
    }
    
    return 0;
}

size_t strlen(const char* s)
{
    int len = 0;

    while (*s) {
        s++;
        len++;
    }

    return len;
}

char* strcpy(char* dst, const char* src)
{
    char* d = dst;

    *dst = *src;
    while (*src) {
        dst++;
        src++;
        *dst = *src;
    }

    return d;
}

int strcmp(const char* s1, const char* s2)
{
    while (*s1 || *s2) {
        if (*s1 != *s2) {
            return (*s1 > *s2) ? 1 : -1;
        }
        s1++;
        s2++;
    }
    
    return 0;
}

int strncmp(const char* s1, const char* s2, size_t n)
{
    while ((*s1 || *s2) && (0 < n)) {
        if (*s1 != *s2) {
            return (*s1 > *s2) ? 1 : -1;
        }
        s1++;
        s2++;
        n--;
    }

    return 0;
}

int putchar(char c)
{
    if (c == '\n') {
        serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    }

    return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

int puts(const char* s)
{
    while (*s) {
        putchar(*s);
        s++;
    }

    return 0;
}

int putxval(unsigned long value, int column)
{
    char buf[PUTXVAL_BUF_SIZE];
    char *p;

    /* ポインタpをバッファの末尾に設定する */
    p = &(buf[PUTXVAL_BUF_SIZE - 1]);

    /* バッファの末尾に'\0'を書き込む */
    *p = '\0';
    p--;

    /* valueが0かつcolumnが0の場合、columnを1にする */
    if (!value && !column) {
        column++;
    }

    /* 16進数をバッファに書き込む */
    while (value || column) {
        *p = "0123456789abcdef"[value & 0xf];
        p--;
        value >>= 4;
        if (column) {
            column--;
        }
    }

    /* 16進数を表示する */
    puts(p + 1);

    return 0;
}
