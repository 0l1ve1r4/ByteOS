// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

#include "../drivers/terminal.h"
#include "../drivers/keyboard.h"

// #include "../include/stdlib.h"

#include "../sys/idt.h"

#include "../userspace/shell.h"

void kernel_main(void){
    terminal_initialize();
    hide_cursor();
    terminal_debug(DEBUG_SUCCESS, "Terminal initialized");

    idt_initialize();
    terminal_debug(DEBUG_SUCCESS, "IDT initialized");
    
    keyboard_initialize();
    terminal_debug(DEBUG_SUCCESS, "Keyboard initialized");

    //heap_initialize();
    //terminal_debug(DEBUG_SUCCESS, "Heap initialized");

    shell_initialize();

}