// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#include "kstdio.h"

int8_t *vidptr;
uint32_t current_loc;                       // current location on the screen
uint32_t buffer_index;                      // index for the input buffer
char input_buffer[BUFFER_SIZE];             // buffer to store input characters

// Initialize the VGA text mode
void stdio_init(void){
    vidptr = (int8_t*) VIDEO_ADDRESS;
    current_loc = 0;
    buffer_index = 0;
}

// Print a formatted string to the screen
void printf(const char* format, ...) {
    if (strcmp(format, " ") == 0 || 
        strcmp(format, "\0") == 0){
        return;
    }

    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd': {
                    uint32_t num = va_arg(args, uint32_t);
                    char* num_str = uint_to_str(num);
                    printf(num_str);
                    break;
                }

                case 'f':{
                    float num = va_arg(args, double);
                    char* num_str = float_to_str(num);
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

                case '%': {                                     // Handle the '%' character e.g "%%"
                    vidptr[current_loc++] = '%';
                    vidptr[current_loc++] = LIGHT_GREY;
                    break;
                }

                default:                                        // Handle unsupported format specifiers
                    vidptr[current_loc++] = '%';
                    vidptr[current_loc++] = LIGHT_GREY;
                    vidptr[current_loc++] = *format;
                    vidptr[current_loc++] = LIGHT_GREY;
                    break;
            }
        } 
        
        else if (*format == '\n') {
            current_loc += (LINE_SIZE - current_loc % (LINE_SIZE));
        }
        
        else {
            vidptr[current_loc++] = *format;
            vidptr[current_loc++] = LIGHT_GREY;
        }
        format++;
    }

    // if reached the end of the screen, scroll the screen
    if (current_loc >= SCREENSIZE) {
        uint32_t j = 0;
        while (j < SCREENSIZE - LINE_SIZE) {
            vidptr[j] = vidptr[j + LINE_SIZE];
            j++;
        }

        while (j < SCREENSIZE) {
            vidptr[j] = ' ';
            vidptr[j + 1] = LIGHT_GREY;
            j = j + 2;
        }
        current_loc = SCREENSIZE - LINE_SIZE;
    }
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
void kclear(void) {
    uint32_t j = 0;
    current_loc = 0;
    while (j < COLUMNS_IN_LINE * LINES * BYTES_EACH_ELEMENT){
        vidptr[j] = ' '; 
        vidptr[j+1] = LIGHT_GREY;
        j = j + 2;
    }
    return;
}

// this functions needs to be here because uses vidptr
void keyboard_handler_main(void) {
    uint8_t status;
    char keycode;

    write_port(0x20, 0x20); // Write EOI

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if (keycode < 0)
            return;

        switch (keycode) {
            case ENTER_KEY_CODE:
                input_buffer[buffer_index] = '\0';            
                kshell(input_buffer); 

                // Clear the input buffer
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
                        vidptr[current_loc + 1] = LIGHT_GREEN;
                    }
                }
                break;

            default:
                if (buffer_index < BUFFER_SIZE - 1) {
                    uint8_t character = keyboard_map[(uint8_t)keycode];
                    input_buffer[buffer_index++] = character;

                    vidptr[current_loc++] = character;
                    vidptr[current_loc++] = 0x07;
                }
                break;
        }
    }
}