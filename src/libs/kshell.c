// This file is part of basicOS.
// Copyright (C) 2024 Guilherme Oliveira Santos

// This is free software: you can redistribute it and/or modify it 
// under the terms of the GNU GPL3 or (at your option) any later version.

// This program is distributed in hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See at LICENSE file for more details.

// Kernel shell implementation, based on this tutorial:
// https://brennan.io/2015/01/16/write-a-shell-in-c/

#include "kshell.h"
#include "kstdlib.h"
#include "kstring.h"
#include "kstdio.h"

// Clear the screen and show the OS prompt
void kshell_init(void) {
    kclear();
    printf(OS_PROMPT);
    printf(SHELL_PROMPT);
} 

char* builtin_str[] = {
    "exit",
    "echo",
    "clear",
    "help",
    "status"
};

char* builtin_desc[] = {
    "Shutdown the kernel",
    "Echo the input",
    "Clear the screen",
    "Show this help message",
    "Show the status of the system"
};

void (*builtin_func[]) (char**) = {
    &shell_exit,
    &shell_echo,
    &shell_clear,
    &shell_help,
    &shell_status

};

size_t num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

void kshell(char* command) {
    printf("\n");
    char** args = split(command, ' ');
    command = args[0];
    char** arguments = args + 1;    

    uint8_t i = 0, status = EXIT_FAILURE;
    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(command, builtin_str[i]) == 0) {
            (*builtin_func[i])(arguments);
            status = EXIT_SUCCESS;
        }
    }

    if (status == EXIT_FAILURE && strcmp(command, "") != 0){
        printf("Command not found: ");
        printf(command);
    }

    printf("\n");
    printf(SHELL_PROMPT);

}

// There are some unused parameters in the functions below
// This is because the functions are pointers to functions
// and they need to have the same signature

#pragma GCC diagnostic ignored "-Wunused-parameter"

void shell_exit(char** args) {
    power_off();
}

void shell_echo(char** args) {
    while (*args) {
        printf("%s ", *args);
        args++;
    }
}

void shell_clear(char** args) {
    kclear();
}

void shell_help(char** args){
    uint8_t description = strcmp(args[0], "-d");
    description == 0 ? printf("Available commands:\n") : printf("Available commands (use -d to show more):\n");    
    printf("\n");
    
    for (uint8_t i = 0; i < num_builtins(); i++) {
        printf("| %s", builtin_str[i]);
        
        if (!description) {
            printf(" | %s", builtin_desc[i]);
        }
        printf("\n");
    }
}

void shell_status(char** args){
    char* str = (char*)malloc(sizeof(char));
    sprintf(str, "Heap: %d/%d", get_heap_used(), get_heap_size());
    printf("%s\n", str);
}

#pragma GCC diagnostic pop