/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

// Read from port function
static inline uint8_t read_port(uint16_t port) {
    uint8_t value;
    __asm__ __volatile__ ("inb %w1, %b0" : "=a" (value) : "Nd" (port));
    return value;
}

// Write to port function
static inline void write_port(uint16_t port, uint8_t value) {
    __asm__ __volatile__ ("outb %b0, %w1" : : "a" (value), "Nd" (port));
}

// Load IDT function
static inline void load_idt(void *idt_ptr) {
    __asm__ __volatile__ ("lidt (%0)" : : "r" (idt_ptr));
    __asm__ __volatile__ ("sti");
}

// Sends a byte to an I/O port  
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));

}

// Reads a byte from an I/O port and returns it
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// Reads 2 bytes value from an I/O port and returns it
static inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    __asm__ volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// Sends a 2 bytes value to an I/O port
static inline void outw(uint16_t port, uint16_t value) {
    __asm__ volatile ("outw %1, %0" : : "dN" (port), "a" (value));
}

#endif // PORTS_H