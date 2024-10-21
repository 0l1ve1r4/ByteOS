#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <types.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

/* reads from the standard input stream stdin. */
int scanf(const char *format, ...);

/* Converts, formats, and writes the data to the character string under control of format. */
int snprintf(const char * restrict s, size_t n, const char * restrict format, ...);

/* writes output to the standard output stream stdout. */
int printf(const char * restrict format, ...);

/* writes the character c (converted to an unsigned char) to stdout. */
int putchar(int c);

/* writes the string pointed to by s to stdout. */
int puts(const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STDIO_H */
