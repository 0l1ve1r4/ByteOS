#ifndef _KERNEL_X86_H
#define _KERNEL_X86_H

#include <stdint.h>

#define GDT_ARR_SIZE 6
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

struct tss {
    uint16_t link;
    uint16_t _reserved;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es  ; 
    uint32_t cs  ; 
    uint32_t ss  ; 
    uint32_t ds  ; 
    uint32_t fs  ; 
    uint32_t gs  ; 
    uint32_t ldtr; 
    uint16_t _reserved10; uint16_t iopb;
    uint32_t ssp;
} __attribute__((packed));

void init_GDT();
void init_IDT();
void init_IRQ();
void init_TSS();
#endif /* _KERNEL_X86_H */
