#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H

#include <types.h>

void kernelHeapInit(void);

void * kMalloc(u32 size);

void kFree(void * pointer);

#endif /* _KERNEL_HEAP_H */

