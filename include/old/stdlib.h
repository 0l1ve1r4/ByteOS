#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include <stddef.h>

#define HEAP_SIZE (uint32_t)(1024 * 1024) * 10     

typedef struct block_header {
    size_t size;                                          
    int free;                                                 
    struct block_header* next;                            
} block_header_t;

void heap_initialize(void);
void* malloc(size_t size);
void free(void* ptr);
uint32_t get_heap_used(void);
uint32_t get_heap_size(void);

#endif // STDLIB_H