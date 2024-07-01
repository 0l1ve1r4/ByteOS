// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#ifndef KSTRING_H
#define KSTRING_H

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

#include "../types.h"

size_t strlen(const char* str);

char* strcpy(char* dest, const char* src);
char* uint_to_str(uint32_t n);
char* float_to_str(float n);
char* strcat(char* dest, const char* src);

uint32_t strcmp(const char* str1, const char* str2);
uint32_t num_length(uint32_t n);

void* memcpy(void* dest, const void* src, size_t n);

size_t count_tokens(const char* str, char delim);
char** split(const char* str, char delim);

#endif // KSTRING_H