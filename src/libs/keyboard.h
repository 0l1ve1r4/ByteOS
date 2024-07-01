// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#ifndef KEYBOARD_H
#define KEYBOARD_H

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#include "../types.h"

#define IDT_SIZE 256                                    // IDT size
#define INTERRUPT_GATE 0x8e                             // Interrupt gate flag
#define KERNEL_CODE_SEGMENT_OFFSET 0x08                 // Kernel code segment offset

struct IDT_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;                                  // Kernel segment selector (0x08)
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
};

// Function prototypes
_PROTOTYPE( void kb_init, (void) );                     // Initialize the keyboard
_PROTOTYPE( void idt_init, (void) );                    // Initialize the IDT
_PROTOTYPE( void keyboard_handler_main, (void) );       // Main keyboard handler

// Function declared in boot/bootloader.asm
extern void keyboard_handler(void);                     // Keyboard handler
extern char read_port(uint16_t port);                   // Read data from a port
extern void write_port(uint16_t port, uint8_t data);    // Write data to a port
extern void load_idt(uint32_t *idt_ptr);                // Load the IDT
extern uint8_t keyboard_map[128];                       // Keyboard map for US layout

#endif