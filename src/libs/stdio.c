// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#include "stdio.h"

static int8_t *vidptr;                             // pointer to video memory
static uint8_t current_color; 

static uint32_t current_loc;                       // current location on the screen
static uint32_t buffer_index;                      // index for the input buffer

static char input_buffer[BUFFER_SIZE];             // buffer to store input characters
static bool is_caps_lock;                          // is the caps lock key pressed?

const char* ANSI_COLORS[] = {
    ANSI_BLACK,
    ANSI_BLUE,
    ANSI_GREEN,
    ANSI_CYAN,
    ANSI_RED,
    ANSI_MAGENTA,
    ANSI_BROWN,
    ANSI_LIGHT_GREY,
    ANSI_DARK_GREY,
    ANSI_LIGHT_BLUE,
    ANSI_LIGHT_GREEN,
    ANSI_LIGHT_CYAN,
    ANSI_LIGHT_RED,
    ANSI_LIGHT_MAGENTA,
    ANSI_LIGHT_BROWN,
    ANSI_WHITE
};

// Initialize the VGA text mode
void stdio_init(void){
    vidptr = (int8_t*) VIDEO_ADDRESS;
    current_color = VGA_COLOR_LIGHT_GREY;
    current_loc = 0;
    buffer_index = 0;
    is_caps_lock = FALSE;
}

char to_uppercase(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

void verify_ansi_colors(const char* format, uint8_t *color) {
    char ansi_code[MAX_UINT32_STR_SIZE];
    uint8_t ansi_index = 0;

    // Copy the ANSI code into ansi_code array
    while (*format != 'm' && ansi_index < MAX_UINT32_STR_SIZE - 1) {
        ansi_code[ansi_index] = *format;
        format++;
        ansi_index++;
    }

    ansi_code[ansi_index] = 'm';
    ansi_code[ansi_index + 1] = '\0';

    for (uint8_t i = 0; i <= VGA_COLOR_WHITE; i++) {
        if (strcmp(ansi_code, ANSI_COLORS[i]) == 0) {
            *color = i;
            return;
        }
    }
}

void printf(const char* format, ...) {
    if (*format == '\0') { 
        return; 
    }

    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '\033'){
            verify_ansi_colors(format, &current_color);
            format += ANSI_ESCAPE_CODES_SIZE; // Skip past the ANSI code
        }

        else if (*format == '%') {
            format++;
            switch (*format) {
                case 'c': {
                    char c = va_arg(args, char);
                    vidptr[current_loc++] = c;
                    vidptr[current_loc++] = current_color;
                    break;
                }

                case 'd': {
                    uint32_t num = va_arg(args, uint32_t);
                    char* num_str = uint_to_str(num);
                    printf(num_str);
                    break;
                }

                case 'f': {
                    double num = va_arg(args, double);
                    char* num_str = float_to_str((float)num);
                    printf(num_str);
                    break;
                }

                case 'i': {
                    uint32_t num = va_arg(args, uint32_t);
                    char* num_str = uint_to_str(num);
                    printf(num_str);
                    break;
                }   

                case 's': {
                    char* str = va_arg(args, char*);
                    printf(str);
                    break;
                }

                case '%': { // Handle the '%' character e.g "%%"
                    vidptr[current_loc++] = '%';
                    vidptr[current_loc++] = current_color;
                    break;
                }

                default: // Handle unsupported format specifiers
                    vidptr[current_loc++] = '%';
                    vidptr[current_loc++] = current_color;
                    vidptr[current_loc++] = *format;
                    vidptr[current_loc++] = current_color;
                    break;
            }
        } else if (*format == '\n') {
            current_loc += (LINE_SIZE - current_loc % (LINE_SIZE));
        } else {
            vidptr[current_loc++] = *format;
            vidptr[current_loc++] = current_color;
        }
        format++;
    }

    // If reached the end scroll the screen
    if (current_loc >= SCREENSIZE) {
        clear_inline();
    }
    
    move_cursor(current_loc / 2);
    va_end(args);
}

// format a string and store it in a buffer
void sprintf(char* buffer, const char* format, ...) {
    if (buffer == NULL || format == NULL)
        return;
    
    va_list args;
    va_start(args, format);

    uint32_t buf_index = 0;
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    uint32_t num = va_arg(args, uint32_t);
                    char* num_str = uint_to_str(num);
                    strcpy(buffer + buf_index, num_str);
                    buf_index += strlen(num_str);
                    break;
                }

                case 'f': {
                    double num = va_arg(args, double);
                    char* num_str = float_to_str(num);
                    strcpy(buffer + buf_index, num_str);
                    buf_index += strlen(num_str);
                    break;
                }

                case 's': {
                    char* str = va_arg(args, char*);
                    uint32_t len = strlen(str);
                    strcpy(buffer + buf_index, str);
                    buf_index += len;
                    break;
                }

                case '%': {
                    buffer[buf_index++] = '%';
                    break;
                }

                default: {
                    buffer[buf_index++] = '%';
                    buffer[buf_index++] = *format;
                    break;
                }
            }
        } else {
            buffer[buf_index++] = *format;
        }
        format++;
    }
    buffer[buf_index] = '\0';  // Null-terminate the buffer
    va_end(args);
}

// Clear the screen
void clear(void) {
    uint32_t j = 0;
    current_loc = 0;
    while (j < COLUMNS_IN_LINE * LINES * BYTES_EACH_ELEMENT){
        vidptr[j] = ' '; 
        vidptr[j+1] = VGA_COLOR_LIGHT_GREY;
        j = j + 2;
    }
    return;
}

// Clear input line (the last one)
void clear_inline(void) {
    for (uint32_t j = 0; j < SCREENSIZE - LINE_SIZE; ++j) {         // Shift lines up by one
        vidptr[j] = vidptr[j + LINE_SIZE];
    }

    uint32_t start = SCREENSIZE - LINE_SIZE;
    for (uint32_t j = start; j < SCREENSIZE; j += 2) {              // Clear the last line
        vidptr[j] = ' ';
        vidptr[j + 1] = VGA_COLOR_LIGHT_GREY;
    }

    current_loc = SCREENSIZE - LINE_SIZE;                           // Update the cursor location
    move_cursor(current_loc / 2);
}

void keyboard_handler_main(void) {
    uint8_t status;
    char keycode;

    write_port(0x20, 0x20); // Write EOI

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if (keycode < 0) {
            return;
        }
    }

    switch (keycode) {
        case ENTER_KEY_CODE:
            input_buffer[buffer_index] = '\0';            
            shell(input_buffer); 
            buffer_index = 0;
            input_buffer[0] = '\0';
            
            break;

        case BACKSPACE_KEY_CODE:
            if (buffer_index > 0) {
                buffer_index--;
                input_buffer[buffer_index] = '\0';

                if (current_loc > 0) {
                    current_loc -= BYTES_EACH_ELEMENT;
                    vidptr[current_loc] = ' ';
                    vidptr[current_loc + 1] = VGA_COLOR_LIGHT_GREY;
                    move_cursor(current_loc / 2);
                }
            }
            
            break;

        case CAPSLOCK_KEY_CODE:
            is_caps_lock = !is_caps_lock;
            
            break;

        default:
            if (buffer_index < BUFFER_SIZE - 1) {
                uint8_t character = keyboard_map[(uint8_t)keycode];
                if (is_caps_lock) {
                    character = to_uppercase(character);
                }

                input_buffer[buffer_index++] = character;

                vidptr[current_loc++] = character;
                vidptr[current_loc++] = 0x07; // Assuming 0x07 is the attribute for the character
                move_cursor(current_loc / 2);
            }
            
            break;
        }
}

// Send bytes to the cursor position register
void move_cursor(uint16_t pos) {
    outb (FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb (FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb (FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb (FB_DATA_PORT, pos & 0x00FF);
}

// Power off the system
void power_off(void) {
    outw(ACPI_PM1A_CNT, SLP_TYPa | SLP_EN);
    outw(ACPI_PM1B_CNT, SLP_TYPb | SLP_EN);
    while (1) __asm__ __volatile__("hlt");
}