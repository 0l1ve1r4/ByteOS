// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#ifndef KSTDIO_H
#define KSTDIO_H

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

#include "keyboard.h"
#include "kstring.h"
#include "kshell.h"
#include "kstdlib.h"

#include "../types.h"
#include "../colors.h"

typedef char* va_list;

#define VIDEO_ADDRESS 0xb8000   
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

// functions to get arguments from the stack
#define ALIGN_SIZE(size, align) (((size) + (align) - 1) & ~((align) - 1))                   // Aligns the size to the nearest multiple of `align`
#define VA_ARG_SIZE(type) ALIGN_SIZE(sizeof(type), sizeof(int))                             // Retrieves the size of the argument type
#define va_start(ap, param) (ap = (va_list)&param + ALIGN_SIZE(sizeof(param), sizeof(int))) // Initializes the `va_list`
#define va_arg(ap, type) (*(type*)((ap += VA_ARG_SIZE(type)) - VA_ARG_SIZE(type)))          // Retrieves the next argument in the list
#define va_end(ap) (ap = (va_list)0)                                                        // Ends the `va_list`

void stdio_init(void);

// Basic functions for video output
void printf(const char* format, ...);
void sprintf(char* buffer, const char* format, ...);

void kclear(void);
void show_info(void);

void keyboard_handler_main(void);

#endif // KSTDIO_H