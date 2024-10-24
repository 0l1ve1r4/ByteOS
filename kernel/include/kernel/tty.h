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

void setTextColor(u8 color);

void setBgColor(u8 color);

/* Initialize the terminal */
u8 init_tty(void);

void terminalPutchar(char c);

/* Write a string to the terminal */
void terminalWrite(const char* data, size_t size);

void terminalNewLine(void);

void terminalClearAll(void);

/* Clear the size character(s) */
void terminalClearChar(int size);

void hideVgaCursor(void);

void showVgaCursor(void);

void updateVgaCursor(u16 pos);

void drawPixel(u16 x, u16 y, char pixel_char, u8 color);

u8 getTerminalBgColor(void);

#endif
