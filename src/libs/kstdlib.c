#include "kstdlib.h"

static uint8_t heap[HEAP_SIZE];
static block_header_t* free_list = (block_header_t*)heap;

void heap_init(void) {
    free_list->size = HEAP_SIZE - sizeof(block_header_t);
    free_list->free = 1;
    free_list->next = NULL;
}

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

void split_block(block_header_t* block, size_t size) {
    block_header_t* new_block = (block_header_t*)((uint8_t*)block + sizeof(block_header_t) + size);
    new_block->size = block->size - size - sizeof(block_header_t);
    new_block->free = 1;
    new_block->next = block->next;
    block->size = size;
    block->free = 0;
    block->next = new_block;
}

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

void* kmalloc(size_t size) {
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

    return (void*)((uint8_t*)block + sizeof(block_header_t));
}

void kfree(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    block_header_t* block = (block_header_t*)((uint8_t*)ptr - sizeof(block_header_t));
    block->free = 1;
    merge_blocks();
}
