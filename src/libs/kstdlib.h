#ifndef KSTDLIB_H
#define KSTDLIB_H

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

#include "../types.h"

#define ACPI_PM1A_CNT  0x604                        // ACPI Power Management 1a Control Register
#define ACPI_PM1B_CNT  0x604                        // ACPI Power Management 1b Control Register
#define SLP_TYPa       0x2000                       // Sleep Type A
#define SLP_TYPb       0x2000                       // Sleep Type B
#define SLP_EN         0x2000                       // Sleep Enable

#define HEAP_SIZE (uint32_t)(1024 * 1024) * 10      // 1MB heap  

typedef struct block_header {
    size_t size;
    int free;
    struct block_header* next;
} block_header_t;

// Memory related functions
void  heap_init(void);  
void *malloc(size_t size);
void  free(void* ptr);
uint32_t get_heap_used(void);
uint32_t get_heap_size(void);

void exit(void);
void outw(uint16_t port, uint16_t value);
void power_off();
#endif // KSTDLIB_H