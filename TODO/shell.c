/* This file is part of basicOS.
    Copyright (C) 2024 Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version. */

#include "shell.h"

#include "../drivers/keyboard.h"
#include "../drivers/terminal.h"
#include "../include/string.h"

// Internal functions
size_t num_builtins(void);
void shell(char* command);
void shell_exit(char** args);
void shell_echo(char** args);
void shell_clear(char** args);
void shell_help(char** args);
void shell_status(char** args);
void shell_color(char** args);

char* builtin_str[] = {
    "poweroff",
    "echo",
    "clear",
    "help",
    "status",
    "color"
};

char* builtin_desc[] = {
    "Shutdown the kernel",
    "Echo the input",
    "Clear the screen",
    "Show this help message",
    "Show the status of the system",
    "Change the color of the shell"
};

// Clear the screen and show the OS prompt
void shell_initialize(void) {
    char* ascii_colors[] = {"\033[94m", "\033[37m"};
    char** os_prompt = split_str(OS_PROMPT, '\n');
    uint8_t i = 0;
    while (*os_prompt) {
        terminal_printf("%s%s\n", ascii_colors[i], *os_prompt);
        os_prompt++;

        if (i == 2) {
            i = 0;
        }
        else {
            i++;
        } 
    }
    terminal_printf("%s", ascii_colors[1]);
    while (1) {
        terminal_printf("\n");
        terminal_printf("root@%skernel%s:$/ ", "\033[92m", "\033[37m");

        char buffer[256];
        buffer[0] = '\0';

        // Wait for input and store it in buffer
        keyboard_scanf(buffer);

        // Process the input with the shell
        shell(buffer);
    }
} 

void (*builtin_func[]) (char**) = {
    &shell_exit,
    &shell_echo,
    &shell_clear,
    &shell_help,
    &shell_status,
    &shell_color
};

size_t num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

void shell(char* command) {
    terminal_printf("\n");
    char** args = split_str(command, ' ');
    command = args[0];
    char** arguments = args + 1;    

    uint8_t i = 0, status = DEBUG_ERROR;
    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(command, builtin_str[i]) == 0) {
            (*builtin_func[i])(arguments);
            status = DEBUG_SUCCESS;
        }
    }

    if (status == DEBUG_ERROR && strcmp(command, "") != 0){
        terminal_printf("Command not found: ");
        terminal_printf(command);
    }

}

// There are some unused parameters in the functions below
// This is because the functions are pointers to functions
// and they need to have the same signature

#pragma GCC diagnostic ignored "-Wunused-parameter"

void shell_exit(char** args) {
    terminal_printf("Shutting down the kernel...\n");
}

void shell_echo(char** args) {
    while (*args) {
        terminal_printf("%s ", *args);
        args++;
    }
}

void shell_clear(char** args) {
    terminal_clear_all();
}

void shell_help(char** args){
    uint8_t description = strcmp(args[0], "-d");
    description == 0 ? terminal_printf("Available commands:\n") : terminal_printf("Available commands (use -d to show more):\n");    
    terminal_printf("\n");
    
    for (uint8_t i = 0; i < num_builtins(); i++) {
        terminal_printf("| %s", builtin_str[i]);
        
        if (!description) {
            terminal_printf(" | %s", builtin_desc[i]);
        }
        terminal_printf("\n");
    }
}

void shell_status(char** args){
    terminal_printf("%s\n", "Not implemented");
}

void shell_color(char** args){
    terminal_printf("Color command\n");
    return;
}

#pragma GCC diagnostic pop