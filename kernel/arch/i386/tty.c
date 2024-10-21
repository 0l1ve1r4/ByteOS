#include <kernel/tty.h>
#include <utils/ports.h>

#include <types.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY (u16*)0xB8000

static size_t terminal_row;
static size_t terminal_column;
static size_t last_wrote_index;
static u8 terminal_color;
static u16* terminal_buffer;

void terminal_roll(void);

static inline u8 vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline u16 vga_entry(unsigned char uc, u8 color) {
    return (u16)uc | (u16)color << 8;
}

static void set_color(u8 fg, u8 bg) {
    terminal_color = vga_entry_color(fg, bg);
}

void set_text_color(u8 color) {
    set_color(color, VGA_COLOR_BLACK);
}

void set_bg_color(u8 color) {
    set_color(VGA_COLOR_LIGHT_GREY, color);
}

u8 init_tty(void) {
    hide_vga_cursor();
    set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    terminal_clear_all();

    return 0;
}

void terminal_setcolor(u8 color) {
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, u8 color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
    last_wrote_index = index;
}

void terminal_putchar(char c) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        if (terminal_row++ == VGA_HEIGHT)
            terminal_roll();
    }
    update_vga_cursor(last_wrote_index);
}

void terminal_write(const char* data, size_t size) {
    if (terminal_row >= VGA_HEIGHT) {
        terminal_roll();
    }
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_newline(void) {
    terminal_column = 0;
    terminal_row++;
}

void terminal_clear_all(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    terminal_row = 0;
    terminal_column = 0;
    last_wrote_index = 0;
}

void terminal_clear_char(int size) {
    while (size > 0 && terminal_column > 0) {
        terminal_buffer[last_wrote_index] = vga_entry(' ', terminal_color);
        terminal_column--;
        last_wrote_index--;
        size--;
    }
    update_vga_cursor(last_wrote_index);
}

void terminal_roll(void) {
    /* Move all the rows up */
    for (size_t l = 1; l < terminal_row; l++) {
        for (size_t c = 0; c < VGA_WIDTH; c++) {
            size_t index = l * VGA_WIDTH + c;
            terminal_putentryat(terminal_buffer[index], terminal_buffer[index] >> 8, c, l - 1);
        }
    }

    /* Clear the last row */
    for (size_t c = 0; c < VGA_WIDTH; c++) {
        terminal_putentryat(' ', VGA_COLOR_BLACK, c, terminal_row - 1);
    }
    terminal_row = VGA_HEIGHT - 1;
}

void hide_vga_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void show_vga_cursor(void) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 1);
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | 1);
}

void update_vga_cursor(u16 pos) {
    pos++;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (u8)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (u8)((pos >> 8) & 0xFF));
}