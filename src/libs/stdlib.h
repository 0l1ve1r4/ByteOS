// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#ifndef STDLIB_H
#define STDLIB_H

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#include "../types.h"

#define HEAP_SIZE (uint32_t)(1024 * 1024) * 10             // 1MB heap  

typedef struct block_header {
    size_t size;                                           // Size of the block
    int free;                                              // Is the block free?                   
    struct block_header* next;                             // Pointer to the next block (Linked list)
} block_header_t;

// Memory related functions, with MINIX prototypes
_PROTOTYPE( void heap_init, (void)                      ); // Initialize the heap
_PROTOTYPE( void* malloc, (size_t size)                 ); // Allocate memory on the heap
_PROTOTYPE( void free, (void* ptr)                      ); // Free memory on the heap
_PROTOTYPE( uint32_t get_heap_used, (void)              ); // Get the heap used size
_PROTOTYPE( uint32_t get_heap_size, (void)              ); // Get the heap size

#endif // STDLIB_H