#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../types.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

struct IDT_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
};

void kb_init(void);
void idt_init(void);
void keyboard_handler_main(void);

// Function declared in boot/bootloader.asm
extern void keyboard_handler(void);
extern char read_port(uint16_t port);
extern void write_port(uint16_t port, uint8_t data);
extern void load_idt(uint32_t *idt_ptr);

// Keyboard map for US layout
extern uint8_t keyboard_map[128];

#endif