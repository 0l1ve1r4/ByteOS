/* This file is part of basicOS, (©) Guilherme Oliveira Santos
    This is free software: you can redistribute it and/or modify it 
    under the terms of the GNU GPL3 or (at your option) any later version.  */

#include "shell.h"

#include <stdio.h>
#include <string.h>

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

/* Count the number of tokens in a string */
size_t count_tokens(const char* str, char delim);

/* Split a string into tokens */
char** split_str(const char* str, char delim);


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
    printf(OS_PROMPT);

    while (1) {
        printf("\n");
        printf("root@%mkernel%m:$/ ", "\033[92m", "\033[37m");

        char buffer[256];
        buffer[0] = '\0';

        // Wait for input and store it in buffer
        scanf(buffer);

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
        printf("Command not found: ");
        printf(command);
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

#pragma GCC diagnostic pop


size_t count_tokens(const char* str, char delim) {
    size_t count = 0;
    uint32_t in_token = 0;
    while (*str) {
        if (*str == delim) {
            in_token = 0;
        } else if (!in_token) {                         // Start of a new token
            in_token = 1;
            count++;
        }
        str++;
    }
    return count;
}

char** split_str(const char* str, char delim) {
    static char tokens[UINT8_MAX][UINT8_MAX]; // Static array for tokens
    static char* result[UINT8_MAX + 1];              // Static array for pointers to tokens
    size_t token_index = 0;

    while (*str && token_index < UINT8_MAX) {
        while (*str == delim) { // Skip delimiters
            str++;
        }

        const char* token_start = str; // Find the end of the token
        size_t token_length = 0;

        while (*str && *str != delim && token_length < UINT8_MAX - 1) {
            str++;
            token_length++;
        }

        if (token_length > 0) { // Copy the token to the static array
            for (size_t i = 0; i < token_length; i++) {
                tokens[token_index][i] = token_start[i];
            }
            tokens[token_index][token_length] = '\0'; // Null-terminate the token
            result[token_index] = tokens[token_index]; // Store the pointer to the token
            token_index++;
        }
    }

    result[token_index] = NULL; // Null-terminate the array of pointers

    return result;
}