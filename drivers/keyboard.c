#include "keyboard.h"
#include "terminal.h"
#include "ports.h"

#include "../include/string.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

bool shifted = false;
bool capslock = false;
bool in_scanf = false;

char input_buffer[UINT8_MAX];

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
    static char last_keycode = 0;
    
    //if (keycode == last_keycode) {
    //    return;
    //}

    last_keycode = keycode;

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
    input_buffer[buffer_index] = '\0';            
    buffer_index = 0;

    if (in_scanf){  
        in_scanf = false;
    }
}

void handle_backspace_key(void) {
    if (buffer_index > 0) {
        buffer_index--;
        input_buffer[buffer_index] = '\0';

        if (current_loc > 0) {
            current_loc -= 2;
            terminal_buffer[current_loc] = ' ';
            terminal_buffer[current_loc + 1] = VGA_COLOR_LIGHT_GREY;
        }
    }
}

void handle_capslock_key(void) {
    capslock = !capslock;
}

void handle_default_key(char keycode) {
    uint8_t character = keyboard_map[(uint8_t)keycode];
    if (capslock) {
        character -= 32;
    }
    input_buffer[buffer_index++] = character;
    terminal_buffer[current_loc++] = character;
    terminal_buffer[current_loc++] = VGA_COLOR_LIGHT_GREY;
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
        uint8_t status = read_keyboard_status();
        if (status & 0x01) {
            handle_keycode(read_keycode());
        }
    }

    // Copy the input buffer to the provided buffer
    read_input(buffer, 256);
}

unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};