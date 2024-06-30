#ifndef KSTDIO_H
#define KSTDIO_H

#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

#include "keyboard.h"
#include "kstring.h"
#include "kshell.h"
#include "kstdlib.h"

#include "../types.h"
#include "../colors.h"

#define VIDEO_ADDRESS 0xb8000   
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

void stdio_init(void);

// Basic functions for video output
void kclear(void);
void kprint(const char *str);
void kprint_nl(void);
void show_info(void);

void scanf(const char* format, ...);    // TODO: Implement this function
void printf(const char* format, ...);   // TODO: Implement this function

void keyboard_handler_main(void);




#endif // KSTDIO_H