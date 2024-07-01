// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#include "stdio.h"

int8_t *vidptr;                             // pointer to video memory
uint32_t current_loc;                       // current location on the screen
uint32_t buffer_index;                      // index for the input buffer
char input_buffer[BUFFER_SIZE];             // buffer to store input characters

static uint8_t current_color; 

// Initialize the VGA text mode
void stdio_init(void){
    vidptr = (int8_t*) VIDEO_ADDRESS;
    current_loc = 0;
    buffer_index = 0;
    current_color = LIGHT_GREY;
}

bool verify_ansi_codes(const char* format, uint8_t *color){
    if (*format == '\033') {
        char ansi_code[MAX_UINT32_STR_SIZE];
        uint8_t ansi_index = 0;

        // Copy the ANSI code into ansi_code array
        while (*format != 'm' && ansi_index < MAX_UINT32_STR_SIZE - 1) {
            ansi_code[ansi_index] = *format;
            format++;
            ansi_index++;
        }

        // Ensure the ansi_code string is null-terminated
        ansi_code[ansi_index] = 'm';
        ansi_code[ansi_index + 1] = '\0';

        // Check the ANSI code against known codes
        if (strcmp(ansi_code, RED_ANSI) == 0) {
            *color = RED;
        } else if (strcmp(ansi_code, GREEN_ANSI) == 0) {
            *color = GREEN;
        } else if (strcmp(ansi_code, BLUE_ANSI) == 0) {
            *color = BLUE;
        } else if (strcmp(ansi_code, LIGHTGREY_ANSI) == 0) {
            *color = LIGHT_GREY;
        }   return TRUE;
    }   return FALSE;
}

void printf(const char* format, ...) {
    if (*format == '\0') { return; }

    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (verify_ansi_codes(format, &current_color)) {
            format += ANSI_ESCAPE_CODES_SIZE; // Skip past the ANSI code
        } else if (*format == '%') {
            format++;
            switch (*format) {
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

    // If reached the end of the screen, scroll the screen
    if (current_loc >= SCREENSIZE) {
        uint32_t j = 0;
        while (j < SCREENSIZE - LINE_SIZE) {
            vidptr[j] = vidptr[j + LINE_SIZE];
            j++;
        }

        while (j < SCREENSIZE) {
            vidptr[j] = ' ';
            vidptr[j + 1] = LIGHT_GREY;
            j += 2;
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
                shell(input_buffer); 

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