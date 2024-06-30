#ifndef KSTRING_H
#define KSTRING_H

#include "../types.h"

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

size_t strlen(const char* str);

char* strcpy(char* dest, const char* src);
char* uint_to_str(uint32_t n);
char* strcat(char* dest, const char* src);

uint32_t strcmp(const char* str1, const char* str2);
uint32_t num_length(uint32_t n);

void* memcpy(void* dest, const void* src, size_t n);

#endif // KSTRING_H