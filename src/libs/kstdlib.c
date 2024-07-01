// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#include "kstdlib.h"

static uint32_t heap_used = 0;
static uint32_t heap[HEAP_SIZE];
static block_header_t* free_list = (block_header_t*)heap;

// Initialize the heap
void heap_init(void) {
    free_list->size = HEAP_SIZE - sizeof(block_header_t);
    free_list->free = 1;
    free_list->next = NULL;
}

// Find a free block in the heap
block_header_t* find_free_block(size_t size) {
    block_header_t* current = free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Split a block into two blocks
void split_block(block_header_t* block, size_t size) {
    block_header_t* new_block = (block_header_t*)((uint8_t*)block + sizeof(block_header_t) + size);
    new_block->size = block->size - size - sizeof(block_header_t);
    new_block->free = 1;
    new_block->next = block->next;
    block->size = size;
    block->free = 0;
    block->next = new_block;
}

// Merge adjacent free blocks
void merge_blocks() {
    block_header_t* current = free_list;
    while (current != NULL && current->next != NULL) {
        if (current->free && current->next->free) {
            current->size += sizeof(block_header_t) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

// Allocate memory on the heap
void* malloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    block_header_t* block = find_free_block(size);
    if (block == NULL) {
        return NULL; 
    }

    if (block->size > size + sizeof(block_header_t)) {
        split_block(block, size);
    } else {
        block->free = 0;
    }
    heap_used += block->size + sizeof(block_header_t);
    return (void*)((uint8_t*)block + sizeof(block_header_t));
}

// Free memory on the heap
void free(void* ptr) {
    if (ptr == NULL) {
        return;
    }
    block_header_t* block = (block_header_t*)((uint8_t*)ptr - sizeof(block_header_t));
    block->free = 1;
    merge_blocks();
}

// Get the amount of heap used
uint32_t get_heap_used(void) {    
    return heap_used;
}

// Get the size of the heap
uint32_t get_heap_size(void) {
    return (uint32_t) HEAP_SIZE;

}

// Power off the system
void power_off(void) {
    outw(ACPI_PM1A_CNT, SLP_TYPa | SLP_EN);                 // Send the shutdown command to the ACPI 
    outw(ACPI_PM1B_CNT, SLP_TYPb | SLP_EN);                 // Power Management Control Registers
    while (1) __asm__ __volatile__("hlt");                  // If ACPI shutdown does not work, halt the CPU
}

// Exit the kernel
void outw(uint16_t port, uint16_t value) {
    __asm__ __volatile__("outw %1, %0" : : "dN" (port), "a" (value));
}