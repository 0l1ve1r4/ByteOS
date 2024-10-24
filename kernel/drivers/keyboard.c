/* This file is part of ByteOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. 
	
	* File: keyboard.c 
	* Description: PS/2 Keyboard driver 
	* Sources: https://osdev.wiki/wiki/PS/2_Keyboard#Scan_Code_Sets 
*/

#include <drivers/keyboard.h>   
#include <utils/ports.h>
#include <kernel/tty.h>

#include <types.h>       
#include <limits.h>     

#define KEYBOARD_DATA_PORT      0x60
#define KEYBOARD_STATUS_PORT    0x64
#define CAPSLOCK_KEY_CODE       0x3A
#define ENTER_KEY_CODE          0x1C
#define BACKSPACE_KEY_CODE      0x0E
#define LSHIFT_KEY_CODE         0x2A

#define UP_ARROW_KEY_CODE       0x48
#define DOWN_ARROW_KEY_CODE     0x50
#define LEFT_ARROW_KEY_CODE     0x4B
#define RIGHT_ARROW_KEY_CODE    0x4D


/* Internal Functions */
void read_input(char *buffer, size_t max_length);
void write_eoi(void);
u8 read_keyboard_status(void);
char read_keycode(void);
void handle_keycode(char keycode);
void handle_enter_key(void);
void handle_backspace_key(void);
void handle_capslock_key(void);
void handle_lshift_key(void);
void handle_default_key(char keycode);
void set_in_scanf(void);

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

char characterTableShift[] = {
    0,    0,    '!',  '@',  '#',  '$',  '%',  '^',  '&',  '*',  '(',  ')',
    '_',  '+',  0,    0x09, 'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',
    'O',  'P',  '{',  '}',  0,    0,    'A',  'S',  'D',  'F',  'G',  'H',
    'J',  'K',  'L',  ':',  '"',  '~',  0,    '|',  'Z',  'X',  'C',  'V',
    'B',  'N',  'M',  '<',  '>',  '?',  0,    '*',  0,    ' ',  0,    0,
};

bool lshift = false;
bool capslock = false;
bool in_scanf = false;

char input_buffer[U8_MAX];
u32 input_buffer_index = 0;

void keyboard_initialize(void) {
    write_port(0x21 , 0xFD);
}

void keyboard_handler(void) {
    write_eoi();
    u8 status = read_keyboard_status();
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

u8 read_keyboard_status(void) {
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

        case LSHIFT_KEY_CODE:
            handle_lshift_key();
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
        terminalNewLine();  
        in_scanf = false;
    }
    
}

void handle_backspace_key(void) {
    if (input_buffer_index == 0) {            
        return;
    }
    input_buffer_index--;

    if (in_scanf) {
        terminalClearChar(1);
    }
}

void handle_capslock_key(void) {
    capslock = !capslock;
}

void handle_lshift_key(void){
    lshift = !lshift;
}

void handle_default_key(char keycode) {
    u8 c;
    if (lshift){
        c = characterTableShift[(u8)keycode];
    } else {
        c = characterTable[(u8)keycode];
    }

    if (capslock) {
        c -= 32;
    }

    input_buffer[input_buffer_index++] = c;
    if (in_scanf) {
        terminalPutchar(c);
    }

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


// Waits the user to press Enter and stores the input in the buffer
void keyboard_scanf(char *buffer) {
    in_scanf = true;

    // Wait for Enter key press
    while (in_scanf) {
        u8 status = read_keyboard_status();
        if (status & 0x01) {
            char keycode = read_keycode();
            if (keycode < 0) {
                continue;
            }

            else if (keycode == UP_ARROW_KEY_CODE){
                buffer[0] = '\0';
                return;
            }

            handle_keycode(keycode);
        }
    }  
    // Copy the input buffer to the provided buffer
    read_input(buffer, U8_MAX);
}
