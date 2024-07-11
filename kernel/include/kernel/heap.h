#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H

#include <stdint.h>

typedef struct _KHEAPBLOCKBM {
    struct _KHEAPBLOCKBM *next;
    uint32_t size;
    uint32_t used;
    uint32_t bsize;
    uint32_t lfb; // Last free block index
} KHEAPBLOCKBM;

/* First block in heap */
typedef struct _KHEAPBM {
    KHEAPBLOCKBM *fblock; 
} KHEAPBM;

/* Initialize a heap block manager	*/
void k_heapBMInit(KHEAPBM *heap);

/* Add a block to the heap block manager	*/
int k_heapBMAddBlock(KHEAPBM *heap, uintptr_t addr, uint32_t size, uint32_t bsize);

/* Allocate memory from the heap block manager	*/
void *k_heapBMAlloc(KHEAPBM *heap, uint32_t size);

/* Free allocated memory in the heap block manager	*/
void k_heapBMFree(KHEAPBM *heap, void *ptr);

#define k_heap_init k_heapBMInit

#define k_add_block k_heapBMAddBlock

#define k_malloc	k_heapBMAlloc

#define k_free		k_heapBMFree

#endif /* _KERNEL_HEAP_H */

