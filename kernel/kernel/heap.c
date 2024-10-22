/* This file is part of ByteOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. 
	
	* File: heap.c 
	* Description: Bit map heap implementation
	* Sources: https://wiki.osdev.org/User:Pancakes/BitmapHeapImplementation
*/

#include <stddef.h>
#include <types.h>
#include <string.h>
#include <stdio.h>
#include <kernel/heap.h>

#define HEAP_SIZE 1024 * 1024  // 1 MB heap
#define BLOCK_SIZE 32          // Block size of 32 bytes

#define HEAP_BLOCKS (HEAP_SIZE / BLOCK_SIZE)
#define BITMAP_SIZE (HEAP_BLOCKS / 8)

static u8 heap[HEAP_SIZE];       // The actual heap memory
static u8 bitmap[BITMAP_SIZE];   // Bitmap to track free/used blocks

/* Initialize bitmap to zero (all blocks are free) */
void initHeap(void) {
    memset(bitmap, 0, sizeof(bitmap));  
}

static void setBit(int index, int value) {
    int byteIndex = index / 8;
    int bitIndex = index % 8;

    if (value)
        bitmap[byteIndex] |= (1 << bitIndex);  
    else
        bitmap[byteIndex] &= ~(1 << bitIndex);  
}

static int getBit(int index) {
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return (bitmap[byteIndex] >> bitIndex) & 1;
}

void *kMalloc(size_t size) {
    if (size == 0 || size > HEAP_SIZE)
        return NULL;

    int blocksNeeded = (size + BLOCK_SIZE - 1) / BLOCK_SIZE; 
    int freeBlocks = 0;
    int startIndex = -1;

    for (int i = 0; i < HEAP_BLOCKS; i++) {
        if (!getBit(i)) {
            if (freeBlocks == 0) startIndex = i;
            freeBlocks++;
            if (freeBlocks == blocksNeeded) {
                for (int j = startIndex; j < startIndex + blocksNeeded; j++) {
                    setBit(j, 1);
                }

                void *allocatedMemory = heap + startIndex * BLOCK_SIZE;
				/* Represents the allocated memory as 'A'*/
                memset(allocatedMemory, ALLOCATION_REPRESENTATION, blocksNeeded * BLOCK_SIZE);

                return allocatedMemory;
            }
        } else {
			/*  Reset if a used block is encountered */
            freeBlocks = 0;  
        }
    }
	printf("[heap.c]: No sufficient contiguous memory found\n");
    return NULL;  
}


void kFree(void *ptr) {
    if (!ptr) return;

    uintptr_t offset = (uintptr_t)ptr - (uintptr_t)heap;

    if (offset >= HEAP_SIZE){
		printf("[heap.c]: Pointer outside heap range\n");
		return;
	} 

    int startIndex = offset / BLOCK_SIZE;

    for (int i = startIndex; i < HEAP_BLOCKS && getBit(i); i++) {
        setBit(i, 0);  
    }
}
