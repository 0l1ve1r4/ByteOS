// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#ifndef STDIO_H 
#define STDIO_H 

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch" // Ignore GCC warning
#include "keyboard.h"               // Keyboard drivers and keyboard_map           
#include "string.h"                 // String manipulation for printf and sprintf     
#include "shell.h"                  // Shell commands needed for keyboard handler
#include "stdarg.h"                 // Variable arguments for printf and sprintf

#include "../types.h"               // Basic types for the kernel
#include "../colors.h"              // VGA text mode colors for ANSI escape codes

// Input/output ports 
#define VIDEO_ADDRESS 0xb8000       // VGA text mode address
#define KEYBOARD_DATA_PORT 0x60     // Keyboard data port
#define KEYBOARD_STATUS_PORT 0x64   // Keyboard status port
#define ENTER_KEY_CODE 0x1C         // Enter key code
#define BACKSPACE_KEY_CODE 0x0E     // Backspace key code

// Screen dimensions 
#define LINES                   (uint8_t) 25
#define COLUMNS_IN_LINE         (uint8_t) 80
#define BYTES_EACH_ELEMENT      (uint8_t) 2
#define LINE_SIZE               (uint16_t) (BYTES_EACH_ELEMENT * COLUMNS_IN_LINE)
#define SCREENSIZE              (uint16_t) (BYTES_EACH_ELEMENT * COLUMNS_IN_LINE * LINES)

// ANSI escape codes, assuming the ANSI code is fixed size 
#define ANSI_ESCAPE_CODES_SIZE 6    // ANSI escape codes are 6 bytes long
#define RED_ANSI "\033[0;31m"       
#define GREEN_ANSI "\033[0;32m"
#define BLUE_ANSI "\033[0;34m"
#define LIGHTGREY_ANSI "\033[0;37m"

// Function prototypes based on MINIX implementation

_PROTOTYPE( void stdio_init, (void)                                         );
_PROTOTYPE( bool verify_ansi_codes, (const char* format, uint8_t *color)    );
_PROTOTYPE( void printf, (const char* format, ...)                          );
_PROTOTYPE( void sprintf, (char* buffer, const char* format, ...)           );
_PROTOTYPE( void kclear, (void)                                             );
_PROTOTYPE( void show_info, (void)                                          );
_PROTOTYPE( void keyboard_handler_main, (void)                              );                                        

#endif // KSTDIO_H