#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stddef.h>

/* Ports */
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

/* Key codes */
#define CAPSLOCK_KEY_CODE 0x3A
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E
#define LSHIFT_KEY_CODE 0x2A

extern uint8_t keyboard_map[128];                                           // Keyboard map for US layout

void keyboard_initialize(void);                                             // Initialize the keyboard
void keyboard_handler_main(void);
void write_eoi(void);
uint8_t read_keyboard_status(void);
char read_keycode(void);
void handle_keycode(char keycode);
void handle_enter_key(void);
void handle_backspace_key(void);
void handle_capslock_key(void);
void handle_default_key(char keycode);

void read_input(char *buffer, size_t max_length);
void keyboard_scanf(char *buffer);

#endif