/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

/* This file implementation is based on ISO/IEC 9899:1999 (E) */

#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void * restrict s1, const void * restrict s2, size_t n);

void *memmove(void *s1, const void *s2, size_t n);

char *strcpy(char* restrict dest, const char* restrict src); 

char *strncpy(char * restrict s1, const char * restrict s2, size_t n);

char *strcat(char * restrict s1, const char * restrict s2);

char *strncat(char * restrict s1, const char * restrict s2, size_t n);

int memcmp(const void *s1, const void *s2, size_t n);

int strcmp(const char *s1, const char *s2);

int strcoll(const char *s1, const char *s2);    // TODO

int strncmp(const char *s1, const char *s2, size_t n); // TODO

size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n); // TODO

void *memchr(const void *s, int c, size_t n); // TODO

char *strchr(const char *s, int c); // TODO

size_t strcspn(const char *s1, const char *s2); // TODO

char *strpbrk(const char *s1, const char *s2); // TODO

char *strrchr(const char *s, int c); // TODO

size_t strspn(const char *s1, const char *s2); // TODO

char *strstr(const char *s1, const char *s2); // TODO

char *strtok(char * restrict s1, const char * restrict s2); // TODO

void *memset(void *s, int c, size_t n);

char *strerror(int errnum); // TODO

size_t strlen(const char *s);

#ifdef __cplusplus
}
#endif

#endif
