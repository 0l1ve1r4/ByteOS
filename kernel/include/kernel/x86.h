#ifndef _KERNEL_X86_H
#define _KERNEL_X86_H

#include <types.h>


#define GDT_ARR_SIZE 6
#define IDT_MAX_DESCRIPTORS 0x20

// Segment descriptor structure
struct gdt_entry {
    u16 limit_low;     // The lower 16 bits of the limit
    u16 base_low;      // The lower 16 bits of the base
    u8 base_middle;    // The next 8 bits of the base
    u8 access;         // Access flags
    u8 granularity;
    u8 base_high;      // The last 8 bits of the base
} __attribute__((packed));

// Pointer to the GDT structure
struct gdt_ptr {
    u16 limit;         // The upper 16 bits of all selector limits
    u32 base;          // The address of the first gdt_entry_t struct
} __attribute__((packed));

typedef struct {
    u16    isr_low;      // The lower 16 bits of the ISR's address
    u16    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
    u8     reserved;     // Set to zero
    u8     attributes;   // Type and attributes; see the IDT page
    u16    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
    u16    limit;
    u32    base;
} __attribute__((packed)) idtr_t;

struct tss {
    u16 link;
    u16 _reserved;
    u32 esp0;
    u32 ss0;
    u32 esp1;
    u32 ss1;
    u32 esp2;
    u32 ss2;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u32 es  ; 
    u32 cs  ; 
    u32 ss  ; 
    u32 ds  ; 
    u32 fs  ; 
    u32 gs  ; 
    u32 ldtr; 
    u16 _reserved10; u16 iopb;
    u32 ssp;
} __attribute__((packed));

u8 init_GDT();

u8 init_IDT();

u8 init_IRQ();

u8 init_TSS();

#endif /* _KERNEL_X86_H */
