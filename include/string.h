// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h> 

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch" // Ignore GCC warning

/*  String functions    */
char* strcpy(char* dest, const char* src); // Copy a string
char* uint_to_str(uint32_t n); // Convert an unsigned integer to a string
char* float_to_str(float n); // Convert a float to a string
char* strcat(char* dest, const char* src); // Concatenate two strings
char** split (const char* str, char delim); // Split a string into tokens

/* size_t               */
size_t strlen(const char* str); // Returns the length of a string
size_t count_tokens(const char* str, char delim); // Count the number of tokens in a string

/*  uint32_t            */
uint32_t strcmp(const char* str1, const char* str2); // Compare two strings
uint32_t num_length(uint32_t n); // Get the length of a number

/*  void                */
void* memcpy(void* dest, const void* src, size_t n); // Copy memory area
void* memset(void* dest, int c, size_t n); // Fill memory with a constant byte

#endif // STRING_H