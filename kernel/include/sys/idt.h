/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. 

Interrupt descriptor table references:
    * https://wiki.osdev.org/Interrupt_Descriptor_Table
    * https://wiki.osdev.org/IDT
    * https://samypesse.gitbook.io/how-to-create-an-operating-system/chapter-6   
    
*/

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef enum idt_interrupts {
    timer_interrupt = 0x00,
    keyboard_interrupt = 0x01,
    cascdade_interrupt = 0x02,
    com2_interrupt = 0x03,
    com1_interrupt = 0x04,
    lpt2_interrupt = 0x05,
    floppy_interrupt = 0x06,
    lpt1_interrupt = 0x07,
    clock_interrupt = 0x08,
    cga_interrupt = 0x09,
    free1_interrupt = 0x0A,
    free2_interrupt = 0x0B,
    ps2_mouse_interrupt = 0x0C,
    co_processor_interrupt = 0x0D,
    primary_ata_interrupt = 0x0E,
    secondary_ata_interrupt = 0x0F,
    
} idt_interrupts_t;

/* Initialize the Interrupt Descriptor Table */
void idt_initialize(void);

#endif // IDT_H