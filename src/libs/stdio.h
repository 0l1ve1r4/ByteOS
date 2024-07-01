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
#include "../kernel/ports.h"                  // I/O ports for VGA text mode

#include "../types.h"               // Basic types for the kernel
#include "../colors.h"              // VGA text mode colors for ANSI escape codes

/* Input/output ports  */ 
#define VIDEO_ADDRESS 0xb8000       // VGA text mode address
#define KEYBOARD_DATA_PORT 0x60     // Keyboard data port
#define KEYBOARD_STATUS_PORT 0x64   // Keyboard status port

/* Key codes    */
#define ENTER_KEY_CODE 0x1C         // Enter key code
#define BACKSPACE_KEY_CODE 0x0E     // Backspace key code
#define LSHIFT_KEY_CODE 0x2A        // Left shift key code
#define ESC_KEY_CODE 0x01           // Escape key code
#define CAPSLOCK_KEY_CODE 0x3A      // Caps lock key code

/* The I/O ports  ref: https://github.com/koder77/mkeykernel/blob/master/src/kernel/io.h */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* The power */
#define ACPI_PM1A_CNT  0x604                               // ACPI Power Management 1a Control Register
#define ACPI_PM1B_CNT  0x604                               // ACPI Power Management 1b Control Register
#define SLP_TYPa       0x2000                              // Sleep Type A
#define SLP_TYPb       0x2000                              // Sleep Type B
#define SLP_EN         0x2000                              // Sleep Enable

// Screen dimensions 
#define LINES                   (uint8_t) 25
#define COLUMNS_IN_LINE         (uint8_t) 80
#define BYTES_EACH_ELEMENT      (uint8_t) 2
#define LINE_SIZE               (uint16_t) (BYTES_EACH_ELEMENT * COLUMNS_IN_LINE)
#define SCREENSIZE              (uint16_t) (BYTES_EACH_ELEMENT * COLUMNS_IN_LINE * LINES)

// ANSI escape codes, assuming the ANSI code is fixed size 
#define ANSI_ESCAPE_CODES_SIZE 4  
#define ANSI_BLACK "\033[30m"
#define ANSI_BLUE "\033[34m"
#define ANSI_GREEN "\033[32m"
#define ANSI_CYAN "\033[36m"
#define ANSI_RED "\033[31m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_BROWN "\033[33m"
#define ANSI_LIGHT_GREY "\033[37m"
#define ANSI_DARK_GREY "\033[90m"
#define ANSI_LIGHT_BLUE "\033[94m"
#define ANSI_LIGHT_GREEN "\033[92m"
#define ANSI_LIGHT_CYAN "\033[96m"
#define ANSI_LIGHT_RED "\033[91m"
#define ANSI_LIGHT_MAGENTA "\033[95m"
#define ANSI_LIGHT_BROWN "\033[93m"
#define ANSI_WHITE "\033[97m"
extern const char* ANSI_COLORS[];

typedef struct {
    char name[11];       // File name (8.3 format)
    uint8_t attr;        // File attributes
    uint8_t ntRes;       // Reserved (Windows NT)
    uint8_t crtTimeTenth;// Created time (tenths of second)
    uint16_t crtTime;    // Created time (hours, minutes, seconds)
    uint16_t crtDate;    // Created date
    uint16_t lstAccDate; // Last accessed date
    uint16_t fstClusHI;  // High 16 bits of first cluster number
    uint16_t wrtTime;    // Last write time
    uint16_t wrtDate;    // Last write date
    uint16_t fstClusLO;  // Low 16 bits of first cluster number
    uint32_t fileSize;   // File size in bytes
} FILE;

// Function prototypes based on MINIX implementation
_PROTOTYPE( void stdio_init, (void)                                         );
_PROTOTYPE( void verify_ansi_colors, (const char* format, uint8_t *color)    );
_PROTOTYPE( char* verify_format, (const char* format)                       );
_PROTOTYPE( char to_uppercase, (char c)                                     );
_PROTOTYPE( void printf, (const char* format, ...)                          );
_PROTOTYPE( void sprintf, (char* buffer, const char* format, ...)           );
_PROTOTYPE( void clear, (void)                                              );
_PROTOTYPE( void clear_inline, (void)                                       ); // Clear the input line (the last one)
_PROTOTYPE( void show_info, (void)                                          );
_PROTOTYPE( void keyboard_handler_main, (void)                              );                                        
_PROTOTYPE( void move_cursor, (uint16_t pos)                                );  // Move the cursor based on current_loc 
_PROTOTYPE( void power_off, (void)                                          );  // Power off the system

#endif // KSTDIO_H