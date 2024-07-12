/* This file is part of ByteOS.
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

/* Copy n characters from src to dest. */ 
void *memcpy(void * restrict s1, const void * restrict s2, size_t n);

/* Move n characters from src to dest, handling overlapping memory blocks correctly. */ 
void *memmove(void *s1, const void *s2, size_t n);

/* Copy the string pointed by src to dest. */ 
/* CRITICAL [MS-banned] (CWE-120). Consider using strncpy */
/* char *strcpy(char* restrict dest, const char* restrict src);*/

/* Copy at most n characters from the string pointed by s2 to s1. */ 
char *strncpy(char * restrict s1, const char * restrict s2, size_t n);

/* Concatenate the string pointed by s2 to the string pointed by s1. */ 
char *strcat(char * restrict s1, const char * restrict s2);

/* Concatenate at most n characters from the string pointed by s2 to the string pointed by s1. */ 
char *strncat(char * restrict s1, const char * restrict s2, size_t n);

/* Compare the first n characters of two memory blocks. */ 
int memcmp(const void *s1, const void *s2, size_t n);

/* Compare two strings. */ 
int strcmp(const char *s1, const char *s2);

/* Compare two strings using the current locale. */ 
int strcoll(const char *s1, const char *s2);    

/* Compare at most the first n characters of two strings. */ 
int strncmp(const char *s1, const char *s2, size_t n); 

/* Transform the string pointed by s2 and place the resulting string into s1. */ 
size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n); 

/* Search for the first occurrence of the character c in the first n characters of the string pointed by s. */ 
void *memchr(const void *s, int c, size_t n); 

/* Search for the first occurrence of the character c in the string pointed by s. */ 
char *strchr(const char *s, int c); 

/* Calculate the length of the initial segment of the string pointed by s1 which consists only of characters not in the string pointed by s2. */ 
size_t strcspn(const char *s1, const char *s2); 

/* Search for the first occurrence of any character from the string pointed by s2 in the string pointed by s1. */ 
char *strpbrk(const char *s1, const char *s2); 

/* Search for the first occurrence of the character c in the string pointed by s, but searching in reverse order. */ 
char *strrchr(const char *s, int c); 

/* Calculate the length of the initial segment of the string pointed by s1 which consists only of characters from the string pointed by s2. */ 
size_t strspn(const char *s1, const char *s2); 

/* Locate the first occurrence in the string pointed by s1 of any character from the string pointed by s2, excluding the terminating null character. */ 
char *strstr(const char *s1, const char *s2); 

/* Split a string into tokens. */ 
char** split_str(const char* str, char delim);

/* Copy n characters from src to dest */
void *memset(void *s, int c, size_t n);

/* Return a pointer to the error message string */
char *strerror(int errnum); 

/* Return the length of the string */
size_t strlen(const char *s);

/* ======== Extras functions ======== */

/* Count the number of tokens in a string */
size_t count_tokens(const char* str, char delim);

/* Split a string into tokens */
char** split_str(const char* str, char delim);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STRING_H */
