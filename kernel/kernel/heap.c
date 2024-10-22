#include <kernel/heap.h>
#include <stdio.h>

typedef struct _KernelHeapBlock {
    struct _KernelHeapBlock *next;
    u32 size;
    u32 used;
    u32 bsize;
    u32 lfb; // Last free block index
} KernelHeapBlock;

/* First block in heap */
typedef struct {
    KernelHeapBlock *fblock; 
} KernelHeapBM;

/* Add a block to the heap block manager	*/
static int kernelHeapAddBlock(KernelHeapBM *heap, uintptr_t addr, u32 size, u32 bsize);

/* Allocate memory from the heap block manager	*/
static void *kernelHeapAlloc(KernelHeapBM *heap, u32 size);

/* Free allocated memory in the heap block manager	*/
static void kernelHeapFree(KernelHeapBM *heap, void *ptr);

static KernelHeapBM kheap;
void kernelHeapInit(void) {
    kheap.fblock = 0;
    kernelHeapAddBlock(&kheap, 0x10000, 0x100000, 16);
}

int kernelHeapAddBlock(KernelHeapBM *heap, uintptr_t addr, u32 size, u32 bsize) {
    KernelHeapBlock *block = (KernelHeapBlock *)addr;
    u32 blockCount, x;
    u8 *bitmap;

    if (size < sizeof(KernelHeapBlock)) {
        printf("Error: Block size too small\n");
        return 0;
    }

    block->size = size - sizeof(KernelHeapBlock);
    block->bsize = bsize;
    block->next = heap->fblock;
    heap->fblock = block;

    blockCount = block->size / block->bsize;
    bitmap = (u8 *)&block[1];

    // Clear bitmap
    for (x = 0; x < blockCount; ++x) {
        bitmap[x] = 0;
    }

    // Reserve room for bitmap
    blockCount = (blockCount / bsize) * bsize < blockCount ? blockCount / bsize + 1 : 
                blockCount / bsize;
    for (x = 0; x < blockCount; ++x) {
        bitmap[x] = 5;
    }
	
    block->lfb = blockCount - 1;
    block->used = blockCount;

    return 1;
}

static u8 k_heapBMGetNID(u8 a, u8 b) {
    u8 c;
    for (c = a + 1; c == b || c == 0; ++c);
    return c;
}

void *kernelHeapAlloc(KernelHeapBM *heap, u32 size) {
    KernelHeapBlock *block;
    u8 *bitmap;
    u32 blockCount, x, y, z, neededBlocks;
    u8 nid;

    // Iterate blocks
    for (block = heap->fblock; block; block = block->next) {
        if (block->size - (block->used * block->bsize) >= size) {
            blockCount = block->size / block->bsize;
            neededBlocks = (size / block->bsize) * block->bsize < size ? size / block->bsize + 1 :
                             size / block->bsize;
            bitmap = (u8 *)&block[1];

            for (x = (block->lfb + 1 >= blockCount ? 0 : block->lfb + 1); x < block->lfb; ++x) {
                if (x >= blockCount) {
                    x = 0;
                }

                if (bitmap[x] == 0) {
                    // Count free blocks
                    for (y = 0; bitmap[x + y] == 0 && y < neededBlocks && 
                                (x + y) < blockCount; ++y);

                    if (y == neededBlocks) {
                        nid = k_heapBMGetNID(bitmap[x - 1], bitmap[x + y]);

                        // Allocate by setting id
                        for (z = 0; z < y; ++z) {
                            bitmap[x + z] = nid;
                        }

                        block->lfb = (x + neededBlocks) - 2;
                        block->used += y;

                        return (void *)(x * block->bsize + (uintptr_t)&block[1]);
                    }

                    x += (y - 1);
                    continue;
                }
            }
        }
    }

	return (void *)(0);

}

void kernelHeapFree(KernelHeapBM *heap, void *ptr) {
    KernelHeapBlock *block;
    uintptr_t ptrOffset;
    u32 blockIndex, x;
    u8 *bitmap;
    u8 id;
    u32 maxBlocks;

    for (block = heap->fblock; block; block = block->next) {
        if ((uintptr_t)ptr > (uintptr_t)block && (uintptr_t)ptr < (uintptr_t)block + 
                                            sizeof(KernelHeapBlock) + block->size) {
            ptrOffset = (uintptr_t)ptr - (uintptr_t)&block[1];
            blockIndex = ptrOffset / block->bsize;
            bitmap = (u8 *)&block[1];
            id = bitmap[blockIndex];
            maxBlocks = block->size / block->bsize;

            for (x = blockIndex; bitmap[x] == id && x < maxBlocks; ++x) {
                bitmap[x] = 0;
            }

            block->used -= x - blockIndex;
            return;
        }
    }

    // This error needs to be raised or reported somehow
    return;
}


void * kMalloc(u32 size){
    return kernelHeapAlloc(&kheap, size);
}

void kFree(void * pointer){
    kernelHeapFree(&kheap, pointer);
}