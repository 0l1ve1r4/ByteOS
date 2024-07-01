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

#define ACPI_PM1A_CNT  0x604                               // ACPI Power Management 1a Control Register
#define ACPI_PM1B_CNT  0x604                               // ACPI Power Management 1b Control Register
#define SLP_TYPa       0x2000                              // Sleep Type A
#define SLP_TYPb       0x2000                              // Sleep Type B
#define SLP_EN         0x2000                              // Sleep Enable
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
_PROTOTYPE( void power_off, (void)                      ); // Power off the system
_PROTOTYPE( void outw, (uint16_t port, uint16_t value)  ); // Write a 16-bit value to a port

#endif // STDLIB_H