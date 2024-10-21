#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <types.h>


enum vga_color {
	VGA_COLOR_BLACK = 0x00,
	VGA_COLOR_BLUE = 0x01,
	VGA_COLOR_GREEN = 0x02,
	VGA_COLOR_CYAN = 0x03,
	VGA_COLOR_RED = 0x04,
	VGA_COLOR_MAGENTA = 0x05,
	VGA_COLOR_BROWN = 0x06,
	VGA_COLOR_LIGHT_GREY = 0x07,
	VGA_COLOR_DARK_GREY = 0x08,
	VGA_COLOR_LIGHT_BLUE = 0x09,
	VGA_COLOR_LIGHT_GREEN = 0x0A,
	VGA_COLOR_LIGHT_CYAN = 0x0B,
	VGA_COLOR_LIGHT_RED = 0x0C,
	VGA_COLOR_LIGHT_MAGENTA = 0x0D,
	VGA_COLOR_LIGHT_BROWN = 0x0E,
	VGA_COLOR_WHITE = 0x0F,
};

/* Set the text color based on the 0x0F VGA color scheme */
void set_text_color(u8 color);

/* Set the background color based on the 0x0F VGA color scheme */
void set_bg_color(u8 color);

/* Initialize the terminal */
u8 init_tty(void);

/* Insert a char in the current VGA buffer */
void terminal_putchar(char c);

/* Write a string to the terminal */
void terminal_write(const char* data, size_t size);

/* Go to the next row */
void terminal_newline(void);

/* Clear the terminal */
void terminal_clear_all(void);

/* Clear a character */
void terminal_clear_char(int size);

/* Hide the VGA cursor */
void hide_vga_cursor(void);

/* Show the VGA cursor */
void show_vga_cursor(void);

/* Update the VGA cursor */
void update_vga_cursor(u16 pos);

#endif
