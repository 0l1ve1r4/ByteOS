#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H

#include <types.h>

#define ALLOCATION_REPRESENTATION 'A'

void initHeap(void);

void *kMalloc(size_t size);

void kFree(void *ptr);

#endif /* _KERNEL_HEAP_H */

