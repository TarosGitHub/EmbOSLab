#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

/* 標準Cライブラリ */
extern void* memset(void* s, int c, size_t n);
extern void* memcpy(void* dst, const void* src, size_t n);
extern int memcmp(const void* b1, const void* b2, size_t n);
extern size_t strlen(const char* s);
extern char* strcpy(char* dst, const char* src);
extern int strcmp(const char* s1, const char* s2);
extern int strncmp(const char* s1, const char* s2, size_t n);
extern int putchar(char c);
extern int puts(const char* s);
extern unsigned char getchar(void);
extern int gets(unsigned char* buf);

/**
 * 数値を16進数で表示する.
 *
 * @param value 数値
 * @param column 表示桁数. 0の場合はvalueの値を最上位桁まで表示する.
 * @return 常に0を返す
 */
extern int putxval(unsigned long value, int column);

#endif
