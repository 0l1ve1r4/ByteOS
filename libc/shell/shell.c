/* This file is part of ByteOS, (©) Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version.  */

#include "shell.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

/* Return the number of builtins shell commands */
size_t num_builtins(void);

/* Shell command handler */
void shell(char* command);

/* defined at kernel/tty for clear built-in*/
extern void terminal_clear_all(void);

/* Commands */
void shell_exit(char** args);
void shell_echo(char** args);
void shell_clear(char** args);
void shell_help(char** args);
void shell_status(char** args);
void shell_color(char** args);
void shell_date(char** args);

char* builtin_str[] = {
    "poweroff",
    "echo",
    "clear",
    "help",
    "status",
    "color",
    "date",
};

char* builtin_desc[] = {
    "Shutdown the kernel",
    "Echo the input",
    "Clear the screen",
    "Show this help message",
    "Show the status of the system",
    "Change the color of the shell",
    "Show the current date",
};

void (*builtin_func[]) (char**) = {
    &shell_exit,
    &shell_echo,
    &shell_clear,
    &shell_help,
    &shell_status,
    &shell_color,
    &shell_date
};

// Clear the screen and show the OS prompt
void shell_initialize(void) {
    
    printf("\n          Welcome to Byte%sOS%s | ", "\033[92m", "\033[37m");
    shell_date(NULL);

    while (1) {
        char buffer[256];
        memset(buffer, '\0', 256);
        
        printf("\n");
        printf("root@%skernel%s:$/ ", "\033[92m", "\033[37m");

        scanf("%d", &buffer);
        shell(buffer);
    }
} 

size_t num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

void shell(char* command) {
    printf("\n");
    char** args = split_str(command, ' ');
    command = args[0];
    char** arguments = args + 1;    

    size_t i = 0, status = 0;
    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(command, builtin_str[i]) == 0) {
            (*builtin_func[i])(arguments);;
            status = 1;
        }
    }

    if (status == 0){
        printf("Command [%s%s%s] not found.\n", "\033[91m", command, "\033[37m");
    }

}

// There are some unused parameters in the functions below
// This is because the functions are pointers to functions
// and they need to have the same signature

#pragma GCC diagnostic ignored "-Wunused-parameter"

void shell_exit(char** args) {
    printf("Shutting down the kernel...\n");
}

void shell_echo(char** args) {
    while (*args) {
        printf("%s ", *args);
        args++;
    }
}

void shell_clear(char** args) {
    terminal_clear_all();
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
    printf("%s\n", "Not implemented");
}

void shell_color(char** args){
    printf("Color command\n");
    return;
}

void shell_date(char** args){
    static tm time;
    static char date_buffer[20];
    static char time_buffer[20];
    time.date_str = date_buffer;
    time.time_str = time_buffer;
    gmtime(&time);
    printf("Date: %s | Time UTC: %s\n", time.date_str, time.time_str);
    
}

#pragma GCC diagnostic pop


