/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_SIZE 256                                    // IDT size
#define INTERRUPT_GATE 0x8e                             // Interrupt gate flag
#define KERNEL_CODE_SEGMENT_OFFSET 0x08                 // Kernel code segment offset

typedef struct IDT_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;                                  // Kernel segment selector (0x08)
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
} IDT_entry_t;

void idt_initialize(void);
void remap_PIC(void);

#endif // IDT_H