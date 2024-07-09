#ifndef _KERNEL_X86_H
#define _KERNEL_X86_H

#include <stdint.h>

#define GDT_ARR_SIZE 3
#define IDT_MAX_DESCRIPTORS 0x20

// Segment descriptor structure
struct gdt_entry {
    uint16_t limit_low;     // The lower 16 bits of the limit
    uint16_t base_low;      // The lower 16 bits of the base
    uint8_t base_middle;    // The next 8 bits of the base
    uint8_t access;         // Access flags
    uint8_t granularity;
    uint8_t base_high;      // The last 8 bits of the base
} __attribute__((packed));

// Pointer to the GDT structure
struct gdt_ptr {
    uint16_t limit;         // The upper 16 bits of all selector limits
    uint32_t base;          // The address of the first gdt_entry_t struct
} __attribute__((packed));

typedef struct {
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
    uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
    uint8_t     reserved;     // Set to zero
    uint8_t     attributes;   // Type and attributes; see the IDT page
    uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t    limit;
    uint32_t    base;
} __attribute__((packed)) idtr_t;

void init_GDT();
void init_IDT();
void init_IRQ();

#endif /* _KERNEL_X86_H */
