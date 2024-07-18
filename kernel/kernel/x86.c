/* What is this stuff?

    Space for the interrupt descriptor table and Tell the CPU where that space is 
    Tell the PIC that you no longer want to use the BIOS defaults 
    ISR handlers (Interrupt Service Routines) for both IRQs and exceptions
    Addresses of the ISR handlers in the appropriate descriptors (in Interrupt Descriptor Table)
    Enable all supported interrupts in the IRQ mask (of the PIC)

   Global Descriptor Table (GDT)
   
    * https://samypesse.gitbook.io/how-to-create-an-operating-system/chapter-6
    * https://wiki.osdev.org/GDT_Tutorial
    * https://en.wikipedia.org/wiki/Global_Descriptor_Table
    * https://wiki.osdev.org/Global_Descriptor_Table 
    
   Programmable interrupt controller (PIC)
   
    * https://en.wikipedia.org/wiki/Programmable_interrupt_controller
    * https://wiki.osdev.org/8259_PIC
    
   Interrupt Descriptor Table (IDT)

    * https://samypesse.gitbook.io/how-to-create-an-operating-system/chapter-7
    * https://en.wikipedia.org/wiki/Interrupt_descriptor_table
    * https://wiki.osdev.org/Interrupt_Descriptor_Table

   Interrupt Request (IRQ) 

    * https://www.techtarget.com/whatis/definition/IRQ-interrupt-request

*/

#include <kernel/x86.h>
#include <utils/ports.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
struct gdt_entry gdt[GDT_ARR_SIZE]; /* GDT Array    */
struct gdt_ptr gp;                  /* GDT Pointer  */
struct tss tss;                     /* Task state segment */
/* Initialize a gdt segment descriptor.*/
void init_gdt_desc(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;
    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access      = access;

}

/* Load the GDT */
static inline void gdt_load() {
    gp.limit = (sizeof(struct gdt_entry) * GDT_ARR_SIZE) - 1;
    gp.base = (uint32_t)&gdt;
    asm volatile("lgdt (%0)" : : "r"(&gp));
    asm volatile("mov $0x10, %%ax; \
                  mov %%ax, %%ds; \
                  mov %%ax, %%es; \
                  mov %%ax, %%fs; \
                  mov %%ax, %%gs; \
                  ljmp $0x08, $next; \
                  next:": : : "eax");

}

/* Init the Global Descriptor Table (Kernel Only) */
uint8_t init_GDT() {
    init_gdt_desc(0x00, 0x00, 0x00, 0x00, 0x00);        /* Null Descriptor  */
    init_gdt_desc(0x01, 0x00, 0xFFFFFFFF, 0x9A, 0xCF);  /* (Kernel) Code Segment     */
    init_gdt_desc(0x02, 0x00, 0xFFFFFFFF, 0x92, 0xCF);  /* (Kernel) Data Segment     */
    gdt_load();
    
    /* Todo: USER, TASK Segments    */
    return 0;
}


/* IDT entries, aligned for performance*/
__attribute__((aligned(0x10))) static idt_entry_t idt[0xFF]; 

void (*isr_stub_table[0XFF])() = { NULL };

static idtr_t idtr;

static void isr_debug(char* str){
    printf("%s [Exception]: %s %s", "\033[91m", "\033[37m", str);
}

void idt_set_descriptor(uint8_t vector, void (*isr)(), uint8_t flags) {
    isr_stub_table[vector] = isr;
    idt[vector].isr_low = (uint32_t)isr & 0xFFFF;
    idt[vector].kernel_cs = 0x08;
    idt[vector].reserved = 0;
    idt[vector].attributes = flags | 0x60;
    idt[vector].isr_high = ((uint32_t)isr >> 16) & 0xFFFF;
}

void isr_divide_by_zero() {
    isr_debug("EXCEPTION: Divide by zero\n");
    __asm__("cli; hlt");
}

void isr_invalid_opcode() {
    isr_debug("EXCEPTION: Invalid opcode\n");
    __asm__("cli; hlt");
}

void isr_page_fault() {
    isr_debug("EXCEPTION: Page fault\n");
    __asm__("cli; hlt");
}

/* Functions to push error and jump to ISR*/
// TODO: Most of these should be implemented in assembly and should push only specific values onto the stack,
// saving registers with pusha and popa and jumping to an exception handler (implemented in C) which will print the exception itself
// and useful information like at which Addresses the exception occured
void isr_stub_divide_by_zero() {
    asm volatile("push $0");
    asm volatile("jmp isr_divide_by_zero");

}

void isr_stub_invalid_opcode() {
    asm volatile("push $0");
    asm volatile("jmp isr_invalid_opcode");

}

void isr_stub_page_fault() {
    asm volatile("push $0");
    asm volatile("jmp isr_page_fault");

}

/* Initialize the Interrupt Descriptor Table */
uint8_t init_IDT() {
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint32_t)&idt;

    idt_set_descriptor(0x00, isr_divide_by_zero, 0x8E); /* 0X00 isr array position      */
    idt_set_descriptor(0x06, isr_invalid_opcode, 0x8E); /* function handler             */
    idt_set_descriptor(0x0E, isr_page_fault,     0x8E); /* 0x8E: 32-bit Interrupt Gate  */
    __asm__("lidt %0" : : "m"(idtr));

    return 0;

}

/* Remap the Programmable interrupt controller */
void remap_PIC() {
    // ICW1: Start initialization of PIC
    outb(0x20, 0x11); // Master PIC
    outb(0xA0, 0x11); // Slave PIC

    // ICW2: Set interrupt vector offsets
    outb(0x21, 0x20); // Master PIC vector offset
    outb(0xA1, 0x28); // Slave PIC vector offset

    // ICW3: Tell Master PIC there is a slave PIC at IRQ2 (0000 0100)
    outb(0x21, 0x04);
    // Tell Slave PIC its cascade identity (0000 0010)
    outb(0xA1, 0x02);

    // ICW4: Set PIC to x86 mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Mask interrupts on both PICs
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);

}
/* at kernel/keyboard.c         */
extern void keyboard_handler(void); 

/* Init the Interrupt Request */
uint8_t init_IRQ() {
    remap_PIC();
    
    /* Map IRQ 1 (keyboard) to vector 33*/
    idt_set_descriptor(0x21, keyboard_handler, 0x8E); 
    
    /* Unmask IRQ 1 (keyboard)          */
    outb(0x21, ~(1 << 1));                          

    __asm__("sti");

    return 0;
}

void tss_write(uint8_t id, uint16_t ss0, uint32_t esp0) {
    memset(&tss, 0, sizeof(struct tss));
    tss.ss0 = ss0;
    tss.esp0 = esp0;
    tss.cs = 0x0b;  // Kernel code segment
    tss.ss = 0x13;  // Kernel data segment
    tss.ds = 0x13;
    tss.es = 0x13;
    tss.fs = 0x13;
    tss.gs = 0x13;

    uint32_t base = (uint32_t)&tss;
    uint32_t limit = base + sizeof(struct tss);
    init_gdt_desc(id, base, limit, 0xE9, 0x00);
}
void tss_flush() {
    asm volatile("ltr %%ax" : : "a"(0x28));
}
uint8_t init_TSS() {
    tss_write(5, 0x10, 0x0);
    tss_flush();

    return 0;
}
