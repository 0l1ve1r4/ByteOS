/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#include "keyboard.h"           // Main header file
#include "terminal.h"           // video driver
#include "ports.h"              // read_port, write_port

#include <stdint.h>             // uint8_t, etc.
#include <stdbool.h>            // bool
#include <stddef.h>             // size_t

#define KEYBOARD_DATA_PORT      0x60
#define KEYBOARD_STATUS_PORT    0x64
#define CAPSLOCK_KEY_CODE       0x3A
#define ENTER_KEY_CODE          0x1C
#define BACKSPACE_KEY_CODE      0x0E
#define LSHIFT_KEY_CODE         0x2A

/* Internal Functions */
void read_input(char *buffer, size_t max_length);
void keyboard_handler_main(void);
void write_eoi(void);
uint8_t read_keyboard_status(void);
char read_keycode(void);
void handle_keycode(char keycode);
void handle_enter_key(void);
void handle_backspace_key(void);
void handle_capslock_key(void);
void handle_default_key(char keycode);

char characterTable[] = {
    0,    0,    '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',
    '-',  '=',  0,    0x09, 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
    'o',  'p',  '[',  ']',  0,    0,    'a',  's',  'd',  'f',  'g',  'h',
    'j',  'k',  'l',  ';',  '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  0,    '*',  0,    ' ',  0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0x1B, 0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0x0E, 0x1C, 0,    0,    0,
    0,    0,    0,    0,    0,    '/',  0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0,
    0,    0,    0,    0,    0,    0,    0,    0x2C
    };


bool capslock = false;
bool in_scanf = false;

char input_buffer[UINT8_MAX];
uint32_t input_buffer_index = 0;

void keyboard_initialize(void) {
    write_port(0x21 , 0xFD);
}

void keyboard_handler_main(void) {
    write_eoi();
    uint8_t status = read_keyboard_status();
    if (status & 0x01) {
        char keycode = read_keycode();
        if (keycode < 0) {
            return;
        }
        handle_keycode(keycode);
    }
}

void write_eoi(void) {
    write_port(0x20, 0x20);
}

uint8_t read_keyboard_status(void) {
    return read_port(KEYBOARD_STATUS_PORT);
}

char read_keycode(void) {
    return read_port(KEYBOARD_DATA_PORT);
}

void handle_keycode(char keycode) {
    switch (keycode) {
        case ENTER_KEY_CODE:
            handle_enter_key();
            break;

        case BACKSPACE_KEY_CODE:
            handle_backspace_key();
            break;

        case CAPSLOCK_KEY_CODE:
            handle_capslock_key();
            break;

        default:
            handle_default_key(keycode);
            break;
    }
}

void handle_enter_key(void) {
    input_buffer[input_buffer_index] = '\0';            
    input_buffer_index = 0;

    if (in_scanf){  
        in_scanf = false;
    }
    terminal_newline();
}

void handle_backspace_key(void) {
    if (input_buffer_index == 0) {              // Avoid deleting the prompt
        return;
    }

    input_buffer_index = input_buffer_index > 0 ? input_buffer_index - 1 : 0;
    terminal_clear_char(1);
}

void handle_capslock_key(void) {
    capslock = !capslock;
}

void handle_default_key(char keycode) {
    uint8_t character = characterTable[(uint8_t)keycode];
    if (capslock) {
        character -= 32;
    }

    input_buffer[input_buffer_index++] = character;

    terminal_printc(character);

}


// Reads a line of input from the keyboard buffer
void read_input(char *buffer, size_t max_length) {
    size_t index = 0;

    while (index < max_length - 1 && input_buffer[index] != '\0') {
        buffer[index] = input_buffer[index];
        index++;
    }

    buffer[index] = '\0';  // Null-terminate the string
}

// Waits for the user to press Enter and stores the input in the provided buffer
void keyboard_scanf(char *buffer) {
    in_scanf = true;

    // Wait for Enter key press
    while (in_scanf) {
        read_keyboard_status();
    }   // keyboard_handler_main is running in the background, so it will handle the Enter key press

    // Copy the input buffer to the provided buffer
    read_input(buffer, 256);
}