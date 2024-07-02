#include "stdlib.h"

static uint32_t heap_used = 0;
static uint32_t heap[HEAP_SIZE];
static block_header_t* free_list = (block_header_t*)heap;

#define BLOCK_SIZE sizeof(block_header_t)

#include "stdio.h"

// Initialize the heap
void heap_initialize(void) {
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
    heap_used += block->size;
    return (void*)((uint8_t*)block + sizeof(block_header_t));
}

// Free memory on the heap
void free(void* ptr) {
    if (ptr == NULL) {
        return;
    }
    block_header_t* block = (block_header_t*)((uint8_t*)ptr - sizeof(block_header_t));
    heap_used -= block->size;
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