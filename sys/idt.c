#include "idt.h"
#include "../drivers/ports.h"


extern void keyboard_handler(void);

IDT_entry_t IDT[IDT_SIZE];

void idt_initialize(void) {
	uint32_t keyboard_address;
	uint32_t idt_address;
	uint32_t idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (unsigned long)keyboard_handler;
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	remap_PIC();

	/* fill the IDT descriptor */
	idt_address = (uint32_t)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void remap_PIC(void) {
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