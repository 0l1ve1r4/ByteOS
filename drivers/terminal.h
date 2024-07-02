/* This file is part of basicOS.
Copyright (C) 2024 Guilherme Oliveira Santos

This is free software: you can redistribute it and/or modify it 
under the terms of the GNU GPL3 or (at your option) any later version. */

#ifndef STDIO_H 
#define STDIO_H 

#include <stdint.h>

#define VGA_ADDRESS     0xB8000         // VGA address
#define SCREEN_WIDTH    80              // Columns in a line 
#define SCREEN_HEIGHT   25              // Number of lines
#define VGA_CHAR_SIZE   2               // Size of a VGA character
#define LINE_SIZE       VGA_CHAR_SIZE * SCREEN_WIDTH    // Size of a line
#define SCREENSIZE      LINE_SIZE * SCREEN_HEIGHT       // Size of the screen
#define ANSI_ESCAPE_CODE_SIZE 4                         // Size of an ANSI escape code

/* Input/output ports  */ 
#define KEYBOARD_DATA_PORT      0x60    // Keyboard data port
#define KEYBOARD_STATUS_PORT    0x64    // Keyboard status port
#define FB_COMMAND_PORT         0x3D4   // VGA command port
#define FB_DATA_PORT            0x3D5   // VGA data port
#define FB_HIGH_BYTE_COMMAND    14      // High byte command
#define FB_LOW_BYTE_COMMAND     15      // Low byte command

enum vga_color {
    VGA_COLOR_BLACK = 0x0,
    VGA_COLOR_BLUE = 0x1,
    VGA_COLOR_GREEN = 0x2,
    VGA_COLOR_CYAN = 0x3,
    VGA_COLOR_RED = 0x4,
    VGA_COLOR_MAGENTA = 0x5,
    VGA_COLOR_BROWN = 0x6,
    VGA_COLOR_LIGHT_GREY = 0x7,
    VGA_COLOR_DARK_GREY = 0x8,
    VGA_COLOR_LIGHT_BLUE = 0x9,
    VGA_COLOR_LIGHT_GREEN = 0xA,
    VGA_COLOR_LIGHT_CYAN = 0xB,
    VGA_COLOR_LIGHT_RED = 0xC,
    VGA_COLOR_LIGHT_MAGENTA = 0xD,
    VGA_COLOR_LIGHT_BROWN = 0xE,
    VGA_COLOR_WHITE = 0xF,

    VGA_NUM_COLORS = 0x10
};

enum debug_id {
    DEBUG_SUCCESS,
    DEBUG_ERROR
};

extern uint8_t current_color;                   
extern uint8_t *terminal_buffer;                   // pointer to video memory
extern uint32_t buffer_index;                      // index for the input buffer
extern uint32_t current_loc;                       // current location on the screen

void terminal_initialize(void);
void verify_ansi_colors(const char* format, uint8_t *color);
void terminal_printf(const char* format, ...);
void terminal_clear(void);
void terminal_clear_line(uint8_t line);
void terminal_debug(uint8_t status, char* message);

void show_cursor(void);
void hide_cursor(void);
void move_cursor(uint16_t pos);

#endif // KSTDIO_H