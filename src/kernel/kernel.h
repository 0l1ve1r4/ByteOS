#ifndef KERNEL_H
#define KERNEL_H

#include "keyboard.h"

#include "../colors.h"
#include "../types.h"
#include "../libs/kstdlib.h"
#include "../libs/kshell.h"

#define VIDEO_ADDRESS 0xb8000   

void kmain(void);

// Basic functions for video output
void kclear(void);
void kprint(const char *str);
void kprint_nl(void);
void kprintf(const char *format, ...);
void get_current_line(char* buffer);
#endif