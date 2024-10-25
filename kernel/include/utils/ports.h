//========================================================================
//    This file is part of ByteOS.
//    Copyright (C) 2024 Guilherme Oliveira Santos
//    This is free software: you can redistribute it and/or modify it 
//    under the terms of the GNU GPL3 or (at your option) any later version. 
//	
//	* File: .h 
//	* Sources: 
//	* Description:  
//========================================================================

//========================================================================
 	                            #ifndef PORTS_H
                                #define PORTS_H
//========================================================================

//========================================================================
// 	                                INCLUDES
//========================================================================

#include <types.h>

//========================================================================
// 	                                FUNCIONS
//========================================================================

// Read from port function
static inline u8 read_port(u16 port) {
    u8 value;
    __asm__ __volatile__ ("inb %w1, %b0" : "=a" (value) : "Nd" (port));
    return value;
}

// Write to port function
static inline void write_port(u16 port, u8 value) {
    __asm__ __volatile__ ("outb %b0, %w1" : : "a" (value), "Nd" (port));
}

// Load IDT function
static inline void load_idt(void *idt_ptr) {
    __asm__ __volatile__ ("lidt (%0)" : : "r" (idt_ptr));
    __asm__ __volatile__ ("sti");
}

// Sends a byte to an I/O port  
static inline void outb(u16 port, u8 value) {
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));

}

// Reads a byte from an I/O port and returns it
static inline u8 inb(u16 port) {
    u8 ret;
    __asm__ volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// Reads 2 bytes value from an I/O port and returns it
static inline u16 inw(u16 port) {
    u16 ret;
    __asm__ volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// Sends a 2 bytes value to an I/O port
static inline void outw(u16 port, u16 value) {
    __asm__ volatile ("outw %1, %0" : : "dN" (port), "a" (value));
}

//========================================================================
 	                                #endif
//========================================================================