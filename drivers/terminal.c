/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#include "terminal.h"
#include "ports.h"
#include "../include/string.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

uint8_t current_color;                   
uint8_t *terminal_buffer;                   // pointer to video memory
uint32_t buffer_index;                      // index for the input buffer
uint32_t current_loc;                       // current location on the screen

const char* ANSI_ESCAPE_CODES[VGA_NUM_COLORS] = {
    "\033[30m", // ANSI_BLACK
    "\033[34m", // ANSI_BLUE
    "\033[32m", // ANSI_GREEN
    "\033[36m", // ANSI_CYAN
    "\033[31m", // ANSI_RED
    "\033[35m", // ANSI_MAGENTA
    "\033[33m", // ANSI_BROWN
    "\033[37m", // ANSI_LIGHT_GREY
    "\033[90m", // ANSI_DARK_GREY
    "\033[94m", // ANSI_LIGHT_BLUE
    "\033[92m", // ANSI_LIGHT_GREEN
    "\033[96m", // ANSI_LIGHT_CYAN
    "\033[91m", // ANSI_LIGHT_RED
    "\033[95m", // ANSI_LIGHT_MAGENTA
    "\033[93m", // ANSI_LIGHT_BROWN
    "\033[97m"  // ANSI_WHITE
};

void terminal_initialize(void){
    terminal_buffer = (uint8_t*) VGA_ADDRESS;
    current_color = VGA_COLOR_LIGHT_GREY;
    current_loc = 0;
    buffer_index = 0;

    terminal_clear();
}

void verify_ansi_colors(const char* format, uint8_t *color) {
    char ansi_code[12];
    uint8_t ansi_index = 0;

    // Copy the ANSI code into ansi_code array
    while (*format != 'm' && ansi_index < 12 - 1) {
        ansi_code[ansi_index] = *format;
        format++;
        ansi_index++;
    }

    ansi_code[ansi_index] = 'm';
    ansi_code[ansi_index + 1] = '\0';

    for (uint8_t i = 0; i <= VGA_COLOR_WHITE; i++) {
        if (strcmp(ansi_code, ANSI_ESCAPE_CODES[i]) == 0) {
            *color = i;
            return;
        }
    }
}

void terminal_printf(const char* format, ...) {
    if (*format == '\0') { 
        return; 
    }

    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '\033'){
            verify_ansi_colors(format, &current_color);
            format += ANSI_ESCAPE_CODE_SIZE; // Skip past the ANSI code
        }

        else if (*format == '%') {
            format++;
            switch (*format) {
                char* str_buffer;

                case 'd': {
                    uint32_t num = va_arg(args, uint32_t);
                    str_buffer = uint_to_str(num);
                    terminal_printf(str_buffer);
                    break;
                }

                case 'f': {
                    double num = va_arg(args, double);
                    str_buffer = float_to_str(num);
                    terminal_printf(str_buffer);
                    break;
                }

                case 'i': {
                    uint32_t num = va_arg(args, uint32_t);
                    str_buffer = uint_to_str(num);
                    terminal_printf(str_buffer);
                    break;
                }   

                case 's': {
                    char* str = va_arg(args, char*);
                    terminal_printf(str);
                    break;
                }

                default: // Handle unsupported format specifiers
                    terminal_buffer[current_loc++] = '%';
                    terminal_buffer[current_loc++] = current_color;
                    terminal_buffer[current_loc++] = '?';
                    terminal_buffer[current_loc++] = current_color;
                    break;
            }
        } else if (*format == '\n') {
            current_loc += (LINE_SIZE - current_loc % (LINE_SIZE));
        } else {
            terminal_buffer[current_loc++] = *format;
            terminal_buffer[current_loc++] = current_color;
        }
        format++;
    }

    if (current_loc >= SCREENSIZE) {
        terminal_clear();           // TODO: Implement scrolling
    }
    
    move_cursor(current_loc / 2);
    va_end(args);
}

// Clear the screen
void terminal_clear(void) {
    uint32_t j = 0;
    current_loc = 0;
    while (j < SCREENSIZE){
        terminal_buffer[j] = ' '; 
        terminal_buffer[j+1] = VGA_COLOR_LIGHT_GREY;
        j = j + 2;
    }
    return;
}

void terminal_debug(uint8_t status, char* message) {
    if (status == DEBUG_SUCCESS) {
        terminal_printf("\033[92m[ OK ] \033[37m%s\n", message);
    } else {
        terminal_printf("\033[31m[ FAILURE ] \033[37m%s\n", message);
    }
}

// This assumes placing it at 0,0 and can be moved seperately
void show_cursor() { 
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 1);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 1);
}

void hide_cursor() {
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

// Send bytes to the cursor position register
void move_cursor(uint16_t pos) {
    outb (FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb (FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb (FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb (FB_DATA_PORT, pos & 0x00FF);
}