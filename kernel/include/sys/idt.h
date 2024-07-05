/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* Initialize the Interrupt Descriptor Table */
void idt_initialize(void);

#endif // IDT_H