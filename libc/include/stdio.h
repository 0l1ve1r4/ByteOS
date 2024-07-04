#ifndef _STDIO_H
#define _STDIO_H 1

#include <stddef.h>
#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

int snprintf ( char * s, size_t n, const char * format, ... );

#ifdef __cplusplus
}
#endif

#endif
