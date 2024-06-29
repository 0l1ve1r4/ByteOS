#ifndef KSTDLIB_H
#define KSTDLIB_H

#include "types.h"

#define HEAP_SIZE 1024 * 1024               // 1MB heap  

typedef struct block_header {
    size_t size;
    int free;
    struct block_header* next;
} block_header_t;

void initialize_heap(void); 
void* kmalloc(size_t size);
void kfree(void* ptr);


#endif // KSTDLIB_H